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

int is_valid_phone_number(const char *phone)
{
    int i = 0;
    
    // Handle empty string or NULL
    if (!phone || !phone[0])
        return 0;
        
    // Optional '+' prefix
    if (phone[i] == '+')
        i++;
        
    // Need at least one digit after '+'
    if (!phone[i])
        return 0;
        
    // Check remaining characters are all digits
    int digit_count = 0;
    for (; phone[i]; i++) {
        if (!isdigit(phone[i]))
            return 0;
        digit_count++;
    }
    
    // Check length requirements (7-15 digits)
    return (digit_count >= 7 && digit_count <= 15);
}

int is_valid_email(const char *email)
{
    const char *at = strchr(email, '@');
    const char *dot = strchr (email, '.');

    return at &&  dot && at < dot;
}

int add_contact_menu(AddressBookInfo *addressbook) {
    ContactInfo currentContact = { "", "", "" }; // Maintain current working contact
    int op;

    do {
        printf("Add Contact Menu\n");
        printf("\n0. Back\n1. Name       : %s\n2. Phone No   : %s\n3. Email ID   : %s\n",
               currentContact.name[0] ? currentContact.name : "N/A",
               currentContact.phone_number[0] ? currentContact.phone_number : "N/A",
               currentContact.email_addresses[0] ? currentContact.email_addresses : "N/A");
        printf("Please select an option: ");

        // Handle invalid input
        if (scanf("%d", &op) != 1) {
            printf("Invalid input, please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        // Clear input buffer after reading valid input
        while (getchar() != '\n');

        // Handle menu options
        switch (op) {
            case 0: // Exit the menu
                printf("Exiting Contact Menu.\n");
                break;

            case 1: // Enter Name
                printf("Enter the name for Contact %d: ", addressbook->count + 1);
                fgets(currentContact.name, sizeof(currentContact.name), stdin);
                currentContact.name[strcspn(currentContact.name, "\n")] = '\0'; // Remove newline
                if(strlen(currentContact.name) == 0)
                {
                    printf("Invalid Name, Name cannot be empty.\n");
                }
                break;

            case 2: // Enter Phone Number
                printf("Enter the phone number for Contact %d: ", addressbook->count + 1);
                fgets(currentContact.phone_number, sizeof(currentContact.phone_number), stdin);
                currentContact.phone_number[strcspn(currentContact.phone_number, "\n")] = '\0';
                if( !is_valid_phone_number (currentContact.phone_number))
                {
                    printf("Invalid Phone Number. Plaase enter a valid phone number.\n");
                    currentContact.phone_number[0] = '\0';
                }
                break;

            case 3: // Enter Email ID
                printf("Enter the email ID for Contact %d: ", addressbook->count + 1);
                fgets(currentContact.email_addresses, sizeof(currentContact.email_addresses), stdin);
                currentContact.email_addresses[strcspn(currentContact.email_addresses, "\n")] = '\0';
                if(!is_valid_email(currentContact.email_addresses))
                {
                    printf("Invalid Email ID.Please enter a valid enail.\n");
                    currentContact.email_addresses[0] = '\0';
                }
                break;

            default: // Invalid option
                printf("Please select a valid option.\n");
        }

        // Save contact when all fields are filled
        if (strlen(currentContact.name) > 0 && strlen(currentContact.phone_number) > 0 &&
            strlen(currentContact.email_addresses) > 0) {
            // Allocate memory for the new contact
            ContactInfo *newList = realloc(addressbook->list, (addressbook->count + 1) * sizeof(ContactInfo));
            if (newList == NULL) {
                printf("Memory allocation failed.\n");
                return e_failure;
            }
            addressbook->list = newList;

            // Save the current contact
            addressbook->list[addressbook->count] = currentContact;
            addressbook->count++;
            printf("Contact saved successfully.\n");

            // Reset currentContact for the next entry
            currentContact = (ContactInfo) { "", "", "" };
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
		fprintf(addressbook ->fp , "SI No : %d\nName: %s\nPhone Number: %s\nEmail_ID : %s\n", addressbook -> count ,  newContact->name, newContact->phone_number, newContact->email_addresses);
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

