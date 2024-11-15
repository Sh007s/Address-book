#include<stdio.h>
#include "main.h"


;int menu()
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

void add_contact_menu()
{
    printf("Add Contact Menu\n");
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

int save()
{
    printf("Save\n");
    return 0;
}

int exit_menu()
{
    printf("Exiting the Address Book, Goodbye !!!\n");
    exit(0);
}

