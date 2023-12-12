#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Defining each class **/
typedef enum Class {
    FIRST_CLASS = 1,
    SECOND_CLASS,
    THIRD_CLASS
}Class;

/**building data structure for the seats **/
typedef struct Seats{
    Class Class;
    char row;
    char column;
}Seats;
/** building a linked list structure for the client **/
typedef struct Clients{
    char name[50];
    int id;
    char dateOfBirth[11];
    char phoneNumber[11];
    char address[100];
    char gender;
    Seats seat;
    struct Clients * next; // pointer to the next element in the linked list
}Clients;
/** functions prototype **/
void mainMenu();
void createList();
void newClient(Clients ** ph);
void deleteClient(Clients **ph, int clientId);
void clientList(Clients ** ph);
void clientEdit(Clients ** ph, int clientId);
void freeSeats();
void classList();
void initializeSeatsAvailability();
void swap (Clients *,Clients*);
int getIndexFromColumn(char column, char columns[]);
void sortClientsByName(Clients **ph);
void markSeatAsAvailable(Clients * current,int value);

#endif // SYSTEM_H_INCLUDED
