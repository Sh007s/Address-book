#include <stdio.h>
#include <string.h>
#include "main.h"
#include "file_ops.h"

int main(int argc, char *argv[])
{
	AddressBookInfo addressbook;
	int ret;

	// Initialize address book
	addressbook.list = NULL;
	addressbook.count = 0;
	addressbook.fp = NULL;

	if (argc == 1)
	{

		printf("Only ./a.out is passed\n");
		addressbook.default_name = DEFAULT_NAME;
		ret = load_file(&addressbook);

		if (ret != e_success)
		{
			printf("Error: Unable to load or create the default file.\n");
			return e_failure;
		}
	}

	else
	{
		printf("Invalid arguments.\n");
		printf("Usage:  ./address_book.csv\n");
		return e_failure;
	}

	int option;
	do
	{
		option = menu();

		if (option == e_invalid)
		{
			printf("Invalid input. Please enter a number between 0 and 6.\n");
			continue;
		}

		switch (option)
		{
		case 0:
		{
			int result = exit_menu();
			if (result == e_success)
			{
				printf("Exiting. Data saved in address_book.csv\n");
			}
			else if (result == e_failure)
			{
				printf("Exiting. No changes saved.\n");
			}
			else if (result == e_invalid)
			{
				printf("Invalid option. Please enter 'N' or 'Y'.\n");
			}
			break;
		}
		case 1:
			if (Add_Contact(&addressbook) == e_success)
			{
				printf("Contact saved successfully.\n");
			}
			break;
		case 2:
			if (Search_Contact(&addressbook) == e_success)
			{
				printf("Contact search completed successfully.\n");
			}
			break;
		case 3:
			if (Edit_Contact(&addressbook) == e_success)
			{
				printf("Contact edited successfully.\n");
			}
			else
			{
				printf("Failed to edit contact.\n");
			}
			break;
		case 4:
			if (Delete_Contact(&addressbook) == e_success)
			{
				printf("Contact deleted successfully.\n");
			}
			break;
		case 5:
			if (List_Contact(&addressbook) == e_success)
			{
				printf("Contact list displayed successfully.\n");
			}
			break;
		case 6:
			if (Save_File(&addressbook) == e_success)
			{
				printf("File saved successfully.\n");
			}
			break;
		default:
			printf("Invalid option. Please try again.\n");
		}
	} while (option != 0);

	if (addressbook.fp != NULL)
	{
		fclose(addressbook.fp);
	}
	return e_success;
}
