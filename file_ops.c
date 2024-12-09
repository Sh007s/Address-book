#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

// Trim whitespace function
char *trim(char *str)
{
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator character
    *(end + 1) = '\0';

    return str;
}

// Updated load_file function
Status load_file(AddressBookInfo *address_book)
{
    // Ensure address book is initialized
    if (address_book == NULL)
    {
        printf("Error: Address book is not initialized.\n");
        return e_failure;
    }

    // Allocate memory for the contact list if not already allocated
    if (address_book->list == NULL)
    {
        address_book->list = malloc(sizeof(ContactInfo) * MAX_CONTACTS);
        if (address_book->list == NULL)
        {
            printf("Error: Memory allocation failed.\n");
            return e_failure;
        }
    }

    // Use the Read_From_CSV function to load data
    Read_From_CSV(address_book, address_book->default_name);

    // Display the loaded contacts
    if (address_book->count > 0)
    {
        printf("\nTotal contacts loaded: %d\n", address_book->count);
        Display_Contacts(address_book);
    }
    else
    {
        printf("\nNo contacts loaded. The address book is empty.\n");
    }

    return e_success;
}

Status Read_From_CSV(AddressBookInfo *address_book, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file %s\n", filename);
        return e_failure;
    }

    // Skip header line
    char header[MAX_STRING_LENGTH];
    fgets(header, sizeof(header), file);

    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        ContactInfo *contact = &address_book->list[address_book->count];

        // Parse CSV line
        char *token = strtok(line, ",");
        contact->Serial_No = atoi(token);

        token = strtok(NULL, ",");
        strcpy(contact->name, token);

         token = strtok(NULL, ",");
         strcpy(contact->phone_number[0], token);
         contact->phone_count = 1;

         token = strtok(NULL, "\n");
         strcpy(contact->email_addresses[0], token);
         contact->email_count = 1;
        
        address_book->count++;
    }

    fclose(file);
    printf("Data loaded successfully from '%s'.\n", filename);
}

Status Display_Contacts(AddressBookInfo *address_book)
{
    printf("Address Book:\n");
    for (int i = 0; i < address_book->count; i++)
    {
        ContactInfo *contact = &address_book->list[i];

        printf("Serial No: %d\n", contact->Serial_No);
        printf("Name: %s\n", contact->name);

        printf("Phone Numbers:\n");
        for (int j = 0; j < contact->phone_count; j++)
        {
            printf("  %d: %s\n", j + 1, contact->phone_number[j]);
        }

        printf("Email Addresses:\n");
        for (int j = 0; j < contact->email_count; j++)
        {
            printf("  %d: %s\n", j + 1, contact->email_addresses[j]);
        }
        printf("\n");
    }
}
