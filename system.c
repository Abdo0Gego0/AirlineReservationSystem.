#include "system.h"

/** Define 2D arrays to represent seat availability for each class**/
int firstClassAvailability[6][6]; // 1st class has 6 rows and 6 columns
int secondClassAvailability[15][6]; // 2nd class has 15 rows and 6 columns
int thirdClassAvailability[8][8]; // 3rd class has 8 rows and 8 columns
/**columns representation as char**/
char arr1[]={'A','C','D','G','H','K'};
char arr2[]={'A','C','D','E','F','G','H','K'};



/** Initialize seat availability data set all seats 1**/
void initializeSeatsAvailability() {
    /** Initialize the availability for the first class**/
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            firstClassAvailability[i][j] = 1; // 1 represents an available seat
        }
    }

    /** Initialize the availability for the second class**/
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 6; ++j) {
            secondClassAvailability[i][j] = 1; // 1 represents an available seat
        }
    }

    /** Initialize the availability for the third class**/
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            thirdClassAvailability[i][j] = 1; // 1 represents an available seat
        }
    }
}
/** Search for the 1st available seat in the required class**/
void findAvailableSeat(Class class, Seats *availableSeat)
{
    int i = 0;
    int j = 0;
    switch (class){
        case FIRST_CLASS :
            for(i=0;i<6;i++){
                for(j=0;j<6;j++){
                    if(firstClassAvailability[i][j]==1){
                        availableSeat->Class = FIRST_CLASS;
                        availableSeat->row = i + 1;         // Rows are numbered from 1
                        availableSeat->column = arr1[j];    // Columns are represented as characters
                        firstClassAvailability[i][j] = 0;   // Mark the seat as booked
                        return;
                    }
                }
            }
            break;
        case SECOND_CLASS :
            for(i=0;i<15;i++){
                for(j=0;j<6;j++){
                    if(secondClassAvailability[i][j]==1){
                        availableSeat->Class = SECOND_CLASS;
                        availableSeat->row = i + 7;          // Rows are numbered from 7
                        availableSeat->column = arr1[j];     // Columns are represented as characters
                        secondClassAvailability[i][j] = 0;   // Mark the seat as booked
                        return;
                }
            }
        }
        break;
        case THIRD_CLASS :
            for(i=0;i<8;i++){
                for(j=0;j<8;j++){
                    if(thirdClassAvailability[i][j]==1){
                        availableSeat->Class = THIRD_CLASS;
                        availableSeat->row = i + 22;        // Rows are numbered from 22
                        availableSeat->column = arr2[j];    // Columns are represented as characters
                        thirdClassAvailability[i][j] = 0;   // Mark the seat as booked
                        return;
                }
            }
        }
        break;
    }
    availableSeat->Class = -1;
}



void newClient(Clients **ph) {
    /** Create a new client node **/
    Clients *newClientNode = (Clients *)malloc(sizeof(Clients));
    Clients *current;
    Seats *newClientSeat = (Seats *)malloc(sizeof(Seats)); // Allocate memory for newClientSeat
    char classChoice;
    /** Get client information from the user **/

    printf("Enter client name: ");
    //scanf("%s", newClientNode->name);
    fflush(stdin);
    fgets(newClientNode->name, sizeof(newClientNode->name), stdin);





    printf("Enter client ID: ");
    scanf("%d", &newClientNode->id);

    printf("Enter client date of birth (YYYY-MM-DD): ");
    scanf("%s", newClientNode->dateOfBirth);

    printf("Enter client phone number: ");
    scanf("%s", newClientNode->phoneNumber);

    printf("Enter client address: ");
    scanf("%s", newClientNode->address);

    printf("Enter client gender (M/F): ");
    scanf(" %c", &newClientNode->gender);

    /** Get the preferred class from the user **/
    printf("Enter preferred class (1 for FIRST_CLASS, 2 for SECOND_CLASS, 3 for THIRD_CLASS): ");

    scanf(" %c", &classChoice);

    /** Validate classChoice **/
    if (classChoice < '1' || classChoice > '3') { // Use character comparison
        printf("Invalid class choice.\n");
        free(newClientNode); // Free the allocated memory
        free(newClientSeat); // Free the allocated memory for newClientSeat
        return;
    }
     /** Set the selected class based on the user's choice **/
    Class selectedClass;
    switch (classChoice) {
        case '1':
            selectedClass = FIRST_CLASS;
            break;
        case '2':
            selectedClass = SECOND_CLASS;
            break;
        case '3':
            selectedClass = THIRD_CLASS;
            break;
    }
     /** Find an available seat for the client **/
    findAvailableSeat(selectedClass, newClientSeat);

    /** Check if a seat is available **/
    if (newClientSeat->Class == -1) {
        printf("Sorry, no available seats in the selected class.\n");
        free(newClientNode); // Free the allocated memory
        free(newClientSeat); // Free the allocated memory for newClientSeat
        return;
    }

    /** Assign the seat to the new client **/
    newClientNode->seat = *newClientSeat; // Copy the seat information

    /** Add the new client to the linked list **/
    newClientNode->next = NULL; // Initialize the next pointer

    /** Check if the linked list is empty **/
    if (*ph == NULL) {
        *ph = newClientNode; // Set the head to the new client node
    }
    else {
    /** Traverse the linked list to find the last node **/
        current = *ph;
        while (current->next != NULL) {
            current = current->next;
        }

        /** Add the new client node to the end of the linked list **/
        current->next = newClientNode;
    }

    printf("New client added successfully!\n");

}

void clientList(Clients **ph) {
    if (*ph == NULL) {
        printf("No clients in the system.\n");
        return;
    }
    printf("\n before sort\n");
    sortClientsByName(ph);
    printf("\n after sort\n");
    Clients *current = *ph;
    printf("Client List:\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-15s | %-15s | %-40s | %-6s | %-5s | %-4s |\n",
           "ID", "Name", "Date of Birth", "Phone Number", "Address", "Gender", "Class", "Seat");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");

    while (current != NULL) {
        printf("| %-5d | %-20s | %-15s | %-15s | %-40s | %-6c | %-5d | %-1c%-2d  |\n",
               current->id, current->name, current->dateOfBirth, current->phoneNumber,
               current->address, current->gender,current->seat.Class, current->seat.column, current->seat.row);
        current = current->next;
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n after print\n");

    current = *ph;
}

void deleteClient(Clients **ph, int clientId) {
    Clients *temp = *ph, *prev = NULL;

    // Check if the head is the one to be deleted
    if (temp != NULL && temp->id == clientId) {
        markSeatAsAvailable(temp,1);
        *ph = temp->next;
        free(temp);
        return;
    }

    // Traverse through the list to find the node
    while (temp != NULL && temp->id != clientId) {
        prev = temp;
        temp = temp->next;
    }

    // ID not found
    if (temp == NULL) {
        printf("There is no client with this ID.\n");
        return;
    }
    markSeatAsAvailable(temp,1);
    // Change the next pointer from the prev node to the next of the current node
    if (prev != NULL) {
        prev->next = temp->next;
    } else {
        // If prev is NULL, it means the node to be deleted is the head
        *ph = temp->next;
    }

    free(temp); // Delete the node
}


void clientEdit(Clients ** ph, int clientId){
     Clients *current = *ph;

    // Search for the client
    while (current != NULL && current->id != clientId) {
        current = current->next;
        printf("test \n");
    }

    // Check if the client was found
    if (current == NULL) {
        printf("Client not found.\n");
        return;
    }

    // Display the current information
    printf("Current Information for Client ID %d:\n", clientId);
    printf("1. Name: %s\n", current->name);
    printf("2. Date of Birth: %s\n", current->dateOfBirth);
    printf("3. Phone Number: %s\n", current->phoneNumber);
    printf("4. Address: %s\n", current->address);
    printf("5. Gender: %c\n", current->gender);
    printf("6. Class: %u\n", current->seat.Class);
    printf("7. Seat: %c%d\n", current->seat.column, current->seat.row);

    // Get user input for the fields to edit
    int choice;
    printf("Enter the number of the field to edit (0 to finish): ");
    scanf("%d", &choice);

    while (choice != 0) {
        switch (choice) {
            case 1:
                printf("Enter new name: ");
                scanf("%s", current->name);
                break;
            case 2:
                printf("Enter new date of birth (YYYY-MM-DD): ");
                scanf("%s", current->dateOfBirth);
                break;
            case 3:
                printf("Enter new phone number: ");
                scanf("%s", current->phoneNumber);
                break;
            case 4:
                printf("Enter new address: ");
                scanf("%s", current->address);
                break;
            case 5:
                printf("Enter new gender (M/F): ");
                scanf(" %c", &current->gender);
                break;
            case 6:
                printf("Enter new class (1 for FIRST_CLASS, 2 for SECOND_CLASS, 3 for THIRD_CLASS): ");
                scanf("%d", (int *)&((current->seat.Class)));
                break;
            case 7:
                printf("Enter new seat (e.g., A1): ");
                scanf(" %c%d",(char *) &(current->seat.column),(int *) &(current->seat.row));
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }

        // Get the next choice
        printf("Enter the number of the field to edit (0 to finish): ");
        scanf("%d", &choice);
    }

    printf("Client information updated successfully!\n");

    current = *ph;
}

void markSeatAsAvailable(Seats *seat,int value) {
    int rowIndex;
    int columnIndex;
    // Mark the seat as available based on its class and position
    switch (seat->Class) {
        case FIRST_CLASS:
            rowIndex = seat->row -1;
            columnIndex = getIndexFromColumn(seat->column, arr1);
            firstClassAvailability[rowIndex][columnIndex] = value;
            break;
        case SECOND_CLASS:
            rowIndex = seat->row -7;
            columnIndex = getIndexFromColumn(seat->column, arr1);
            secondClassAvailability[rowIndex][columnIndex] = value;
            break;
        case THIRD_CLASS:
            rowIndex = seat->row -22;
            columnIndex = getIndexFromColumn(seat->column, arr2);
            thirdClassAvailability[rowIndex][columnIndex] = value;
            break;
        default:
            // Invalid seat class
            break;
    }
}
int getIndexFromColumn(char column, char columns[]) {
    // Find the index of the column in the specified array
    for (int i = 0; columns[i] != '\0'; ++i) {
        if (columns[i] == column) {
            return i;
        }
    }

    // Return -1 if the column is not found (error case)
    return -1;
}
void freeSeats() {
    printf("Free Seats:\n");
    printf("----------------------------------\n");
    printf("| %-12s | %-15s |\n", "Class", "Free Seats");
    printf("----------------------------------\n");

    int i, j;
    int firstClassFreeSeats = 0, secondClassFreeSeats = 0, thirdClassFreeSeats = 0;

    // Count available seats in each class
    for (i = 0; i < 6; ++i) {
        for (j = 0; j < 6; ++j) {
            if (firstClassAvailability[i][j] == 1) {
                firstClassFreeSeats++;
            }
        }
    }

    for (i = 0; i < 15; ++i) {
        for (j = 0; j < 6; ++j) {
            if (secondClassAvailability[i][j] == 1) {
                secondClassFreeSeats++;
            }
        }
    }

    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            if (thirdClassAvailability[i][j] == 1) {
                thirdClassFreeSeats++;
            }
        }
    }

    // Display the information
    printf("| %-12s | %-15d |\n", "First Class", firstClassFreeSeats);
    printf("| %-12s | %-15d |\n", "Second Class", secondClassFreeSeats);
    printf("| %-12s | %-15d |\n", "Third Class", thirdClassFreeSeats);

    printf("----------------------------------\n");
}
void swap(Clients *a, Clients *b) {
    Clients temp = *a;
    *a = *b;
    *b = temp;
}
void sortClientsByClass(Clients **ph){
    Clients *temp = *ph;
    Clients *ptr1, *ptr2;
    int swapped , i;

    // Bubble sort
    for (i = 1; i <= 3; ++i) {
        ptr1 = temp;
        swapped = 0;

        while (ptr1->next != NULL) {
            ptr2 = ptr1->next;

            // Check if clients need to be swapped based on seat information
            if (ptr1->seat.Class > ptr2->seat.Class ||(ptr1->seat.Class == ptr2->seat.Class && ptr1->seat.row > ptr2->seat.row) ||
                (ptr1->seat.Class == ptr2->seat.Class && ptr1->seat.row == ptr2->seat.row && ptr1->seat.column > ptr2->seat.column))
                {
                swap(ptr1, ptr2);
                swapped = 1;
            }

            ptr1 = ptr1->next;
        }

        // If no swapping occurred, the list is already sorted
        if (!swapped) {
            break;
        }
    }
}
void sortClientsByName(Clients **ph){
    Clients *temp = *ph;
    int swapped;

    do {
        Clients *ptr1 = temp;
        swapped = 0;

        while (ptr1->next != NULL) {
            Clients *ptr2 = ptr1->next;

            if (strcmp(ptr1->name, ptr2->name) > 0) {
                swap(ptr1, ptr2);
                swapped = 1;
            }

            ptr1 = ptr1->next;
        }
    } while (swapped);
}


void classList(Clients **ph) {
    printf("\nClass List:\n");
    printf("-------------------------------------------------------------------------\n");
    printf("| %-6s | %-5s | %-20s | %-6s | %-5s | %-7s |\n",
           "Class", "ID", "Name", "Gender", "Seat", "Date of Birth");
    printf("-------------------------------------------------------------------------\n");

//    sortClientsByClass(ph); // Sort clients before displaying class list

    for (int i = 1; i <= 3; ++i) { // Iterate over each class
        Class currentClass = (Class)i;
        Clients *current = *ph;

        while (current != NULL) {
            if (current->seat.Class == currentClass) {
                printf("| %-6d | %-5d | %-20s | %-6c | %-5c%d | %-10s |\n",
                       currentClass, current->id, current->name,
                       current->gender, current->seat.column, current->seat.row,
                       current->dateOfBirth);
            }
            current = current->next;
        }
    }

    printf("-------------------------------------------------------------------------\n");
}

void mainMenu(Clients **head) {
    int choice;
    int clientId;

    while (1) {
        printf("Main Menu:\n");
        printf("1. Add New Client\n");
        printf("2. Delete Client\n");
        printf("3. Edit Client Information\n");
        printf("4. View Client List\n");
        printf("5. View Available Seats\n");
        printf("6. View Class List\n");
        printf("7. Quit\n");


        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                newClient(head);
                break;
            case 2:
                printf("Enter the ID of the client to delete: ");
                scanf("%d", &clientId);
                deleteClient(head, clientId);
                break;
            case 3:
                printf("Enter the ID of the client to edit: ");
                scanf("%d", &clientId);
                clientEdit(head, clientId);
                break;
            case 4:
                clientList(head);
                break;
            case 5:
                freeSeats();
                break;
            case 6:
                classList(head);
                break;
            case 7:
                printf("Quitting the program. Goodbye!\n");
                return;
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
                break;
        }
    }
}
