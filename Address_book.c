#include<stdio.h>
#include "main.h"

int menu()
{
    int op;
    printf("########  Address Book ########\n");
    printf("########  Feature: \n");

    printf("0.Exit \n1.Add Contact \n2.Search Contact \n3.Edit Contact \n4.Delete Contact \n");
    printf("5.List Contact \n6.Save \n");
    printf("Plase Select an option : ");
    
    if(scanf("%d", &op) != 1)
    {
	while(getchar() != '\n');
	return -1;
    }
    return op;
}

int add_contact_menu(AddressBookInfo *addressbook) {
    ContactInfo newContact = { "", "", "" };
    ContactInfo currentContact = { "", "", "" }; // Add this to maintain current working contact
    int op;
    do {
        printf("Add Contact Menu\n");
        printf("\n0.Back\n1.Name        : \n2.Phone No      :\n3.Email ID       :  \n");
        printf("Please select an option : ");
        // Handle invalid input
        if (scanf("%d", &op) != 1) {
            printf("Invalid input, please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        switch (op) {
            case 0: // Exit the menu
                printf("Exiting Contact Menu\n");
                break;
            case 1: // Enter Name
                printf("Enter the name: ");
                while (getchar() != '\n'); // Clear input buffer
                fgets(currentContact.name, sizeof(currentContact.name), stdin);
                currentContact.name[strcspn(currentContact.name, "\n")] = '\0'; // Remove newline
                break;
            case 2: // Enter Phone Number
                printf("Enter Phone Number: ");
                while (getchar() != '\n');
                fgets(currentContact.phone_number, sizeof(currentContact.phone_number), stdin);
                currentContact.phone_number[strcspn(currentContact.phone_number, "\n")] = '\0';
                break;
            case 3: // Enter Email ID
                printf("Enter Email ID: ");
                while (getchar() != '\n');
                fgets(currentContact.email_addresses, sizeof(currentContact.email_addresses), stdin);
                currentContact.email_addresses[strcspn(currentContact.email_addresses, "\n")] = '\0';
                break;
            default: // Invalid option
                printf("Please select a valid option.\n");
        }
        // Save contact when all fields are filled
        if (strlen(currentContact.name) > 0 && strlen(currentContact.phone_number) > 0 && strlen(currentContact.email_addresses) > 0) {
            addressbook->list = realloc(addressbook->list, (addressbook->count + 1) * sizeof(ContactInfo));
            if (addressbook->list == NULL) {
                printf("Memory allocation failed.\n");
                return e_failure;
            }
            addressbook->list[addressbook->count] = currentContact;
            addressbook->count++;
            printf("Contact saved successfully.\n");
            // Reset contact for the next entry
            memset(&currentContact, 0, sizeof(ContactInfo));
        }
    } while (op != 0);
    return e_success;
}
void add_search_menu()
{
    printf("Add Search Menu\n");
}
void add_edit_menu()
{
    printf("Add Edit Menu\n");
}
void add_delete_menu()
{
    printf("Add Delete Menu\n");
}
void add_list_menu()
{
    printf("Add List Menu\n");
}

int save_files(AddressBookInfo *addressbook)
{
    if(addressbook -> fp == NULL)
	{
		printf("Error : File Pointer is NULL.\n");
		return e_failure;
	}

	for( int i = 0; i < addressbook -> count ; i++)
	{
		ContactInfo *newContact = &addressbook -> list[i];
		fprintf(addressbook ->fp , "Name: %s\nPhone Number: %s\nEmail_ID : %s\n", newContact->name, newContact->phone_number, newContact->email_addresses);
		if( ferror(addressbook -> fp))
		{
			printf("Error writing to the files\n");
			return e_failure;
		}
	}
		
    return e_success;
}

int exit_menu()
{
    printf("Exiting the Address Book, Goodbye !!!\n");
    exit(0);
}

