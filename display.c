//
// Created by tommy on 3/7/2019.
//

#include "display.h"
#include "libraries.h"
#include "avlTree.h"
#include "catalogs.h"

Movie* StartUp()
{
    printf("\n\nWelcome to the IMDb Movie Catalog!\n\n");
    printf("Initializing database. Please wait.\n");
    Movie *tree = LoadDatabase();
    printf("Intitialization finished.\n\n");

    return tree;
}


int MainMenu()
{
    bool loop = false;
    int choice, digit;
    char input[200];

    printf("\nWould you like to:\n");
    printf("(1) Create a new catalog\n");
    printf("(2) Edit an existing catalog\n");
    printf("(3) Close program\n");

    while(! loop)
    {
        printf("\nEnter number of choice: ");
        scanf("%s", input);
        digit = CheckInputIsDigit(input);
        if(digit != -1)
        {
            choice = digit;
            loop = CheckValidInput(1, 3, choice);
        }
    }
    return choice;
}

bool CheckValidInput(int lower, int upper, int num)
{
    bool valid;
    if( (num < lower) || (num > upper) )
    {
        printf("Error: Enter a number %d through %d.\n", lower, upper);
        valid = false;
    }
    else
    {
        valid = true;
    }
    return valid;
}

int CheckInputIsDigit(char *input)
{
    int len = strlen(input);
    if(len != 1)
    {
        printf("ERROR: Single integer digit expected.\n");
        return -1;
    }
    else if (isdigit(input[0]))
        return atoi(input);
    else
    {
        printf("ERROR: Single integer digit expected.\n");
        return -1;
    }
}

void UseCatalogMenu(Movie* database, char* name)
{
    int choice, digit;
    bool loop;
    bool editing = true;
    char input[200];
    Movie *catalogTree = LoadCatalog(name);
    char titleToUse[TITLE_SPACE];

    while(editing) {
        loop = false;
        while (!loop) {
            printf("\nSelect what you would like to do with catalog %s:\n", name);
            printf("(1) Add/Create a movie\n");
            printf("(2) Remove a movie\n");
            printf("(3) Update a movie's media type\n");
            printf("(4) Update a movie's date of acquisition\n");
            printf("(5) View a movie\n");
            printf("(6) View all titles\n");
            printf("(7) Return to main menu\n");
            printf("Enter number of choice: ");
            scanf("%s", input);
            digit = CheckInputIsDigit(input);
            if(digit != -1)
            {
                choice = digit;
                loop = CheckValidInput(1, 7, choice);
            }
        }

        switch (choice) {
            case 1:
                catalogTree = InsertToCatalog(database, catalogTree);
                break;
            case 2:
                printf("\nEnter full exact title of movie to be deleted: ");
                scanf(" %[^\n]", titleToUse);
                catalogTree = Remove(catalogTree, ConvertToKey(titleToUse));
                break;
            case 3:
                printf("\nEnter full exact title of movie to be updated: ");
                scanf(" %[^\n]", titleToUse);
                catalogTree = InitializeMediaTypeMenu(catalogTree, ConvertToKey(titleToUse));
                break;
            case 4:
                printf("\nEnter full exact title of movie to be updated: ");
                scanf(" %[^\n]", titleToUse);
                catalogTree = InitializeDateMenu(catalogTree, ConvertToKey(titleToUse)); //had issue with A Day Without Lies after changing media type
                break;
            case 5:
                printf("\nEnter full exact title of movie to be view: ");
                scanf(" %[^\n]", titleToUse);
                PrintOneMovie(catalogTree, ConvertToKey(titleToUse));
                break;
            case 6:
                PrintAll(catalogTree);
                break;
            case 7:
            default:
                editing = false;
                break;
        }
    }

    FILE* writeFile = NULL;
    writeFile = fopen(name, "w");

    if(catalogTree == NULL)
    {
        fprintf(writeFile, "0\n");
        //printf("\nNOTICE: No movies left in this catalog, so it will be deleted. You can make a new catalog of the same name.");
    }
    else
    {
        fprintf(writeFile, "1\n");
        PrintNodeToFile(catalogTree, writeFile);
    }

    fclose(writeFile);

    return;
}

Movie *InitializeMediaTypeMenu(Movie *catalogTree, char *name)
{
    char input[200];
    bool loop = false;
    int digit, choice;

    printf("Choose the media type of the movie\n");
    printf("(1) dvd\n");
    printf("(2) bluray\n");
    printf("(3) digital\n");
    while(! loop)
    {
        printf("Enter number of choice: ");
        scanf("%s", input);
        digit = CheckInputIsDigit(input);
        if (digit != -1) {
            choice = digit;
            loop = CheckValidInput(1, 3, choice);
        }
    }
    if(choice == 1)
        catalogTree = UpdateMediaType(catalogTree, name, "dvd");
    else if(choice == 2)
        catalogTree = UpdateMediaType(catalogTree, name, "bluray");
    else
        catalogTree = UpdateMediaType(catalogTree, name, "digital");
    return catalogTree;

}

Movie *InitializeDateMenu(Movie *catalogTree, char *name)
{
    char input[200];
    bool loop = false;
    int len;
    while(! loop)
    {
        printf("Enter date that the movie was acquired in form of MM/DD/YYYY: ");
        scanf("%s", input);
        len = strlen(input);
        if(len == 10)
        {
            loop = true;
        }
        else
        {
            printf("ERROR: Date not entered in form of MM/DD/YYYY\n");
        }
    }
    catalogTree = UpdateDate(catalogTree, name, input);
    return catalogTree;

}

