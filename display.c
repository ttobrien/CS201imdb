//
// Created by tommy on 3/7/2019.
//

#include "display.h"
#include "libraries.h"
#include "avlTree.h"

void StartUp()
{
    printf("\n\nWelcome to the IMDb Movie Catalog!\n\n");
    printf("Initializing database. Please wait.\n");
    printf("Intitialization finished.\n\n");

    return;
}


int MainMenu()
{
    int retVal = 0;
    bool loop = false;
    int choice;

    printf("\nWould you like to:\n");
    printf("(1) Create a new catalog\n");
    printf("(2) Edit an existing catalog\n");
    printf("(3) Close program\n");

    while(! loop)
    {
        printf("\nEnter number of choice: ");
        scanf("%d", &choice);
        loop = CheckValidInput(1, 3, choice);
    }
    return choice;
}

bool CheckValidInput(int lower, int upper, int num)
{
    bool liang;
    if( (num < lower) || (num > upper) )
    {
        printf("Error: Enter a number %d through %d.\n", lower, upper);
        liang = false;
    }
    else
    {
        liang = true;
    }
    return liang;
}

void UseCatalogMenu(char* name)
{
    int choice;
    bool loop = false;

    while(!loop) {
        printf("\nSelect what you would like to do with catalog %s:\n");
        printf("(1) Add/Create a movie\n");
        printf("(2) Remove a movie\n");
        printf("(3) Update a movie\n");
        printf("(4) View a movie\n");
        printf("(5) View all titles\n");
        printf("(6) Return to main menu\n");
        printf("Enter number of choice: ");
        scanf("%d", &choice);
        loop = CheckValidInput(1, 6, choice);
    }

    switch(choice)
    {
        case 1:
            Insert(name);
            break;
        case 2:
            Remove(name);
            break;
        case 3:
            Update(name);
            break;
        case 4:
            PrintMovie(name);
            break;
        case 5:
            PrintAll();
            break;
        case 6:
            MainMenu();
            break;
    }
    return;
}

Movie ShowOptions( head)//should get passed in linked list
{
    if(head == NULL)
    {
        printf("No movies found containing the entered string.");
        printf("Note that movies beginning with: \"A\", \"Le\", \"The\", have had those substrings appended to the end of the title with a comma.");

        //recall the previous function
    }
    else
    {
        //copy pointer to perform count
        //copy pointer to print names
        //print titles with a number before each one
        //allow user
        //check input with my function
        //convert to key
        //return movie struct
    }
}


