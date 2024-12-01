#include <stdio.h>
#include <stdlib.h>
#include "file_ops.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

Status load_file(AddressBookInfo *address_book)
{
    // Check if the default file name is set
    if (address_book->default_name == NULL)
    {
        printf("Error: Default file name is not set.\n");
        return e_failure;
    }

    // Attempt to open the file in read mode
    address_book->fp = fopen(address_book->default_name, "r");
    if (address_book->fp == NULL)
    {
        // If the file doesn't exist, create it in write mode
        printf("File '%s' not found. Creating a new file.\n", address_book->default_name);
        address_book->fp = fopen(address_book->default_name, "w");
        if (address_book->fp == NULL)
        {
            printf("Error: Unable to create the file '%s'.\n", address_book->default_name);
            return e_failure;
        }

        // Close the file after creation
        fclose(address_book->fp);

        // Reopen in read/write mode
        address_book->fp = fopen(address_book->default_name, "r+");
        if (address_book->fp == NULL)
        {
            printf("Error: Unable to open the newly created file '%s'.\n", address_book->default_name);
            return e_failure;
        }
    }
    else
    {
        // If the file exists, reopen it in read/write mode
        fclose(address_book->fp);
        address_book->fp = fopen(address_book->default_name, "r+");
        if (address_book->fp == NULL)
        {
            printf("Error: Unable to open the existing file '%s' in read/write mode.\n", address_book->default_name);
            return e_failure;
        }
    }

    printf("File '%s' loaded successfully.\n", address_book->default_name);
    return e_success;
}
