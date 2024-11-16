#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro definitions
#define DEFAULT_NAME      "address_book.csv"
#define NAME_LEN          32
#define NUMBER_LEN        32
#define EMAIL_ID_LEN      64

// Enum for function statuses
typedef enum
{
    e_success = 0,
    e_failure = 1
} Status;

// Structure for storing contact information
typedef struct
{
    char name[NAME_LEN];
    char phone_number[NUMBER_LEN];
    char email_addresses[EMAIL_ID_LEN];
} ContactInfo;

// Structure for managing the address book
typedef struct 
{
    FILE *fp;                					  // File pointer for the CSV file
    ContactInfo *list;         				  // Array of contact information
    int count;           				          // Number of contacts

    char *default_name;   				          // Default file name
} AddressBookInfo;

// Function declarations
int menu();                    				   // Displays the main menu and returns the selected option
int exit_menu();               				   // Handles the exit operation
int add_contact_menu(AddressBookInfo *addressbook);              // Handles adding a new contact
void add_search_menu();     					   // Handles searching for a contact
void add_edit_menu();      					   // Handles editing a contact
void add_delete_menu();      					   // Handles deleting a contact
void add_list_menu();        					   // Handles listing all contacts
int save_files(AddressBookInfo *addressbook);       // Saves the contacts to a file

#endif // MAIN_H

