//
// Created by Tommy O'Brien on 3/7/2019.
//

#include "display.h"
#include "libraries.h"
#include "avlTree.h"
#include "catalogs.h"


Movie* StartUp()
{
    printf("\n\nWelcome to the IMDb Movie Catalog!\n\n");
    printf("Initializing database. Please wait.\n");
    Movie *tree = LoadDatabase();   //getting database of Movies
    printf("Intitialization finished.\n\n");

    return tree;
}


int MainMenu()
{
    bool loop = false;
    int choice, digit;
    char input[INPUT_LEN];

    printf("\nWould you like to:\n");
    printf("(1) Create a new catalog\n");
    printf("(2) Edit an existing catalog\n");
    printf("(3) Close program\n");

    while(! loop)
    {
        printf("\nEnter number of choice: ");
        scanf(" %250[^\n]", input);
        if(strlen(input) == INPUT_LEN)
        {
            printf("\nERROR: Maximum input length exceeded. Program closing. No catalog data was lost.\n");
            exit(1);
        }
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
        printf("ERROR: Enter a number %d through %d.\n", lower, upper);
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
    char input[INPUT_LEN];
    Movie *catalogTree = LoadCatalog(name);
    char titleToUse[TITLE_SPACE];

    while(editing) {
        loop = false;
        while (!loop) {
            printf("\nSelect what you would like to do with catalog %s:\n", name);
            printf("(1) Add a movie\n");
            printf("(2) Remove a movie\n");
            printf("(3) Update a movie's media type\n");
            printf("(4) Update a movie's date of acquisition\n");
            printf("(5) View a movie\n");
            printf("(6) View all info for all movies in the catalog\n");
            printf("(7) Save catalog and return to main menu\n");
            printf("Enter number of choice: ");
            scanf(" %250[^\n]", input);

            if(strlen(input) == INPUT_LEN)
            {
                FILE* writeFile = NULL;
                writeFile = fopen(name, "w");

                if(catalogTree == NULL)
                {
                    fprintf(writeFile, "0\n");
                }
                else
                {
                    fprintf(writeFile, "1\n");
                    PrintNodeToFile(catalogTree, writeFile);
                }

                fclose(writeFile);
                printf("\nEntered amount of characters exceeds limit. Program closing. No catalog data was lost.\n");
                exit(1);
            }

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
                strcpy(titleToUse, GetTitleToUse(catalogTree, name, "deleted"));
                catalogTree = Remove(catalogTree, ConvertToKey(titleToUse));
                break;
            case 3:
                strcpy(titleToUse, GetTitleToUse(catalogTree, name, "updated"));
                catalogTree = InitializeMediaTypeMenu(catalogTree, ConvertToKey(titleToUse));
                break;
            case 4:
                strcpy(titleToUse, GetTitleToUse(catalogTree, name, "updated"));
                catalogTree = InitializeDateMenu(catalogTree, ConvertToKey(titleToUse)); //had issue with A Day Without Lies after changing media type
                break;
            case 5:
                strcpy(titleToUse, GetTitleToUse(catalogTree, name, "viewed"));
                PrintOneMovie(catalogTree, ConvertToKey(titleToUse));
                break;
            case 6:
                printf("\n");
                if (catalogTree == NULL)
                    printf("This catalog contains 0 movies at the moment\n");
                else
                    PrintAll(catalogTree);
                break;
            case 7:
            default:
                editing = false;    //ends loop
                break;
        }
    }

    FILE* writeFile = NULL;     //the subsequent several lines of code save the current catalog
    writeFile = fopen(name, "w");

    if(catalogTree == NULL)
    {
        fprintf(writeFile, "0\n");
    }
    else
    {
        fprintf(writeFile, "1\n");
        PrintNodeToFile(catalogTree, writeFile);
    }

    fclose(writeFile);

    return;
}

char *GetTitleToUse(Movie* catalogTree, char* catalogName, char* action)
{
    char *input;
    input = (char *)malloc(INPUT_LEN * sizeof(char));

    printf("\nEnter full exact title of movie to be %s: ", action);

    scanf(" %250[^\n]", input);

    if(strlen(input) == INPUT_LEN)  //will close program but will save the catalog first
    {
        FILE* writeFile = NULL;
        writeFile = fopen(catalogName, "w");

        if(catalogTree == NULL)
        {
            fprintf(writeFile, "0\n");
        }
        else
        {
            fprintf(writeFile, "1\n");
            PrintNodeToFile(catalogTree, writeFile);
        }

        fclose(writeFile);
        printf("\nEntered amount of characters exceeds limit. Program closing. No catalog data was lost.\n");
        exit(1);
    }

    return input;
}

Movie *InitializeMediaTypeMenu(Movie *catalogTree, char *name)
{
    char input[INPUT_LEN];
    bool loop = false;
    int digit;
    int choice = 0;

    printf("Choose the media type of the movie\n");
    printf("(1) dvd\n");
    printf("(2) bluray\n");
    printf("(3) digital\n");
    while(! loop)
    {
        printf("Enter number of choice: ");
        scanf(" %250[^\n]", input);

        if(strlen(input) == INPUT_LEN)
        {
            printf("\nFATAL ERROR: Entered amount of characters exceeds limit. Program closing. Catalog data may be lost.\n");
            exit(1);
        }

        digit = CheckInputIsDigit(input);
        if (digit != -1)
        {
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
    char input[INPUT_LEN];
    bool loop = false;

    while(! loop)
    {
        printf("Enter date that the movie was acquired in form of MM/DD/YYYY: ");
        scanf(" %250[^\n]", input);

        if(strlen(input) == INPUT_LEN)
        {
            printf("\nFATAL ERROR: Entered amount of characters exceeds limit. Program closing. Catalog data may be lost.\n");
            exit(1);
        }
        else if(strlen(input) == 10)    //the date form of MM/DD/YYYY is 10 characters long
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
