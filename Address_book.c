#include<stdio.h>
#include "main.h"

typedef struct 
{
    char name[NAME_LEN];
    char phone_number[NUMBER_LEN];
    char email_address[EMAIL_ID_LEN];
    int  Serial_No;
}TEMP;



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

int search_contacts(AddressBookInfo *addressbook, TEMP *temp, ContactInfo *results, int max_results) {
    int result_count = 0;

    for (int i = 0; i < addressbook->count; i++) {
        ContactInfo *contact = &addressbook->list[i];

        // Match any criteria (case-insensitive for strings, exact match for Serial_No)
        if ((strlen(temp->name) > 0 && strcasecmp(contact->name, temp->name) == 0) ||
            (strlen(temp->phone_number) > 0 && strcmp(contact->phone_number, temp->phone_number) == 0) ||
            (strlen(temp->email_address) > 0 && strcasecmp(contact->email_addresses, temp->email_address) == 0) ||
            (temp->Serial_No >= 0 && contact->Serial_No == temp->Serial_No)) {
            
            // Add match to results (check for overflow)
            if (result_count < max_results) {
                results[result_count++] = *contact;
            } else {
                printf("Warning: Maximum result limit reached.\n");
                break;
            }
        }
    }
    return result_count;
}

void display_results(ContactInfo *results, int count, TEMP *temp) {
    ContactInfo filtered_results[count]; // Temporary array to store filtered results
    int filtered_count = 0;

    // Filter results based on search criteria in `temp`
    for (int i = 0; i < count; i++) {
        if (strlen(temp->name) > 0 && strcmp(results[i].name, temp->name) != 0) {
            continue; // Skip non-matching names
        }
        if (strlen(temp->phone_number) > 0 && strcmp(results[i].phone_number, temp->phone_number) != 0) {
            continue; // Skip non-matching phone numbers
        }
        if (strlen(temp->email_address) > 0 && strcmp(results[i].email_addresses, temp->email_address) != 0) {
            continue; // Skip non-matching email addresses
        }
        if (temp->Serial_No > 0 && results[i].Serial_No != temp->Serial_No) {
            continue; // Skip non-matching serial numbers
        }
        filtered_results[filtered_count++] = results[i]; // Add matching result to filtered list
    }

    if (filtered_count == 0) {
        printf("No matching contacts found.\n");
        return;
    }

    char quit;
    do {
        printf("\n#### Search Results ####\n");
        printf("============================================================\n");
        printf(": S.No : Name       : Phone No    : Email ID             :\n");
        printf("============================================================\n");
        for (int i = 0; i < filtered_count; i++) {
            printf(": %-4d : %-10s : %-10s : %-20s :\n",
                   filtered_results[i].Serial_No, filtered_results[i].name,
                   filtered_results[i].phone_number, filtered_results[i].email_addresses);
            // Stop after showing only the filtered results
        }
        printf("============================================================\n");

        printf("Press [q] to Cancel : ");
        scanf(" %c", &quit); // Added a space before %c to consume leftover newline character

        // Clear the input buffer to prevent issues with leftover characters
        while (getchar() != '\n');
    } while (quit != 'q' && quit != 'Q');

    // Clear the search criteria when 'q' is pressed
    if (quit == 'q' || quit == 'Q') {
        memset(temp->name, 0, sizeof(temp->name));
        memset(temp->phone_number, 0, sizeof(temp->phone_number));
        memset(temp->email_address, 0, sizeof(temp->email_address));
        temp->Serial_No = -1; // Reset Serial_No
        printf("Search criteria cleared.\n");
    }
}

int add_contact_menu(AddressBookInfo *addressbook) {
    ContactInfo currentContact = { "", "", "" }; // Maintain current working contact
    currentContact.Serial_No = 1;
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
                currentContact.Serial_No = addressbook->count;
                fgets(currentContact.name, sizeof(currentContact.name), stdin);
                currentContact.name[strcspn(currentContact.name, "\n")] = '\0'; // Remove newline
                if (strlen(currentContact.name) == 0) {
                    printf("Invalid Name, Name cannot be empty.\n");
                }
                break;

            case 2: // Enter Phone Number
                printf("Enter the phone number for Contact %d: ", addressbook->count + 1);
                currentContact.Serial_No = addressbook->count;
                fgets(currentContact.phone_number, sizeof(currentContact.phone_number), stdin);
                currentContact.phone_number[strcspn(currentContact.phone_number, "\n")] = '\0';
                if (!is_valid_phone_number(currentContact.phone_number)) {
                    printf("Invalid Phone Number. Please enter a valid phone number.\n");
                    currentContact.phone_number[0] = '\0';
                }
                break;

            case 3: // Enter Email ID
                printf("Enter the email ID for Contact %d: ", addressbook->count + 1);
                currentContact.Serial_No = addressbook->count;
                fgets(currentContact.email_addresses, sizeof(currentContact.email_addresses), stdin);
                currentContact.email_addresses[strcspn(currentContact.email_addresses, "\n")] = '\0';
                if (!is_valid_email(currentContact.email_addresses)) {
                    printf("Invalid Email ID. Please enter a valid email.\n");
                    currentContact.email_addresses[0] = '\0';
                }
                break;

            default: // Invalid option
                printf("Please select a valid option.\n");
        }

        // Save contact when all fields are filled
        if (strlen(currentContact.name) > 0 && strlen(currentContact.phone_number) > 0 &&
            strlen(currentContact.email_addresses) > 0) {

            // **Duplicate Check**
            for (int i = 0; i < addressbook->count; i++) {
                if (strcasecmp(addressbook->list[i].name, currentContact.name) == 0 &&
                    strcasecmp(addressbook->list[i].phone_number, currentContact.phone_number) == 0) {
                    printf("Contact already exists.\n");
                    // Reset currentContact and return to menu
                    currentContact = (ContactInfo) { "", "", "", 0 };
                    break;
                }
            }

            // Only add if no duplicate was found
            if (strlen(currentContact.name) > 0) {
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
                currentContact.Serial_No++;
                printf("Contact saved successfully.\n");

                // Reset currentContact for the next entry
                currentContact = (ContactInfo) { "", "", "", 0 };
            }
        }
    } while (op != 0);

    return e_success;
}

int add_search_menu(AddressBookInfo *addressbook) {
    TEMP temp = { "", "", "", 1 }; // Initialize search criteria
    int op;
    do {
        printf("Add Search Menu\n");
        printf("\n0. Back\n1. Name\n2. Phone No\n3. Email ID\n4. Serial No\n");
        printf("Please select an option: ");

        if (scanf("%d", &op) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        switch (op) {
            case 0:
                printf("Exiting Search Menu.\n");
                break;

            case 1:
                printf("Enter Name: ");
                fgets(temp.name, sizeof(temp.name), stdin);
                temp.name[strcspn(temp.name, "\n")] = '\0'; // Remove newline
                break;

            case 2:
                printf("Enter Phone Number: ");
                fgets(temp.phone_number, sizeof(temp.phone_number), stdin);
                temp.phone_number[strcspn(temp.phone_number, "\n")] = '\0';
                break;

            case 3:
                printf("Enter Email ID: ");
                fgets(temp.email_address, sizeof(temp.email_address), stdin);
                temp.email_address[strcspn(temp.email_address, "\n")] = '\0';
                break;

            case 4:
                printf("Enter Serial No: ");
                if (scanf("%d", &temp.Serial_No) != 1) {
                    printf("Invalid input for Serial No.\n");
                    while (getchar() != '\n');
                    temp.Serial_No = -1;
                }
                break;

            default:
                printf("Invalid option. Try again.\n");
        }

        if (op > 0 && op <= 4) {
            ContactInfo results[MAX_RESULTS];
            int result_count = search_contacts(addressbook, &temp, results, MAX_RESULTS);
            if (result_count > 0) {
                // Pass temp (the search criteria) along with results and result_count
                display_results(results, result_count, &temp);
                
                memset(&temp, 0, sizeof(temp));
            } else {
                printf("No contacts found matching the criteria.\n");
            }
        }

    } while (op != 0);

    return 0;
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
		fprintf(addressbook ->fp , "SI No : %d\nName: %s\nPhone Number: %s\nEmail_ID : %s\n", newContact->Serial_No ,  newContact->name, newContact->phone_number, newContact->email_addresses);
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

