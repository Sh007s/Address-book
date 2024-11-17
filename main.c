#include<stdio.h>
#include "main.h"

int main(int argc, char *argv[])
{ 
    AddressBookInfo addressbook;

    if( argc == 1)
    {
	printf("only ./a.out is passed\n");
        addressbook.default_name = DEFAULT_NAME;
        addressbook.fp = fopen(addressbook.default_name, "w");
  	if(addressbook.fp == NULL)
	{
	    printf("Error opening file\n");
	    return e_failure;
	}
	printf("File name is %s\n", addressbook.default_name);	
    }
    else if (argc == 2)
    {
	if(( strstr(argv[1] , ".csv" )  == NULL))
    	{
    	    printf("argv[1] is not .csv file\n");
    	    printf("Usage : ./a.out address_book.csv\n");
    	    return e_failure;
    	}
   
    	addressbook.fp = fopen(argv[1], "w");
    	if(addressbook.fp == NULL)
    	{
    	    printf("Error opening file\n");
    	    return e_failure;
    	}
	printf("File name is %s\n", argv[1]);
    }
    else
    {
	printf("Pass Valid Argument\n");
	printf("Usage : ./a.out address_book.csv\n");
	return e_failure;
    }

    addressbook.list = NULL;
    addressbook.count = 0;

    int option;   
    do
    {
	option = menu();

	if( option == -1)
	{
	    printf("Invalid input, please enter the number between 0 to 6\n");
	}

    	switch(option)
    	{
    	    case 0:
		{
		    exit_menu();
		    return e_failure;
		}
    	    case 1:
		if(add_contact_menu(&addressbook) == e_success)
		{
		    printf("Back\n");
		}
    		break ;
    	    case 2:
		if(add_search_menu(&addressbook) == e_success)
      		break ;
    	    case 3:
		add_edit_menu();
   		break ;
    	    case 4:
		add_delete_menu();
    		break ;
	    case 5:
		add_list_menu();
	       	break ;
     	    case 6:
		if(save_files(&addressbook) == e_success)
		{
			printf("File Saved Successfully\n");
		}
		break ;
	    default :
		printf("Enter the valid Option\n");
    	}
    }while( option != 0);

    if( addressbook.fp != NULL)
    {
	fclose(addressbook.fp);
    }
    return e_success;
}
