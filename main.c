#include "system.h"


int main()
{
    initializeSeatsAvailability();
    Clients *head =NULL;
    mainMenu(&head);
    return 0;
}
