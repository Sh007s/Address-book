#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Macro definitions
#define DEFAULT_NAME "address_book.csv"
#define NAME_LEN            100
#define NUMBER_LEN          15
#define EMAIL_ID_LEN        50
#define MAX_RESULTS         100
#define MAX_PHONE_NUMBERS    5
#define MAX_EMAIL_IDS        5

// Enum for function statuses
typedef enum
{
    e_success = 0,
    e_failure = 1,
    e_invalid = -1

} Status;

// Structure for storing contact information

typedef struct
{
    char name[NAME_LEN];                               // Name of the contact
    char phone_number[MAX_PHONE_NUMBERS][NUMBER_LEN];  // Array of phone numbers
    char email_addresses[MAX_EMAIL_IDS][EMAIL_ID_LEN]; // Array of email addresses
    int Serial_No;                                     // Serial number of the contact
} ContactInfo;

// Structure for managing the address book
typedef struct
{
    FILE *fp;          // File pointer for the CSV file
    ContactInfo *list; // Array of contact information
    int count;         // Number of contacts

    char *default_name; // Default file name
} AddressBookInfo;

// Function declarations
int menu();                      // Displays the main menu and returns the selected option
Status exit_menu(AddressBookInfo *addressbook);      // Handles the exit operation
Status Add_Contact(AddressBookInfo *addressbook);    // Handles adding a new contact
Status Search_Contact(AddressBookInfo *addressbook); // Handles searching for a contact
Status Edit_Contact(AddressBookInfo *addressbook);   // Handles editing a contact
Status Delete_Contact(AddressBookInfo *addressbook); // Handles deleting a contact
Status List_Contact(AddressBookInfo *addressbook);   // Handles listing all contacts
Status Save_File(AddressBookInfo *addressbook);      // Saves the contacts to a file
Status Search_Menu(ContactInfo *criteria);

#endif // MAIN_H
