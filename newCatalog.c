//
// Created by tommy on 3/7/2019.
//

#include "newCatalog.h"
#include "display.h"
#include "libraries.h"
#include "catalogs.h"




void NewCatalog(Movie *database)
{
    char name[FILENAME_LEN];
    char input[INPUT_LEN];
    bool exists = true;
    int inLen;
    char extention[10];
    bool match = true;
    int count = 0;
    int spaces = 0;

    while(exists)
    {
        spaces = 0;
        count = 0;
        
        printf("\nWhat would you like to name this catalog? ");
        scanf(" %250[^\n]", input);
        if(strlen(input) == INPUT_LEN)
        {
            printf("\nERROR: Maximum input length exceeded. Program closing. No catalog data was lost.\n");
            exit(1);
        }
        else
        {

            inLen = strlen(input);
            strcpy(extention, ".txt");

            if(inLen < 5)
            {
                printf("\nERROR: file name should be at least 5 characters long because of the file's name and the .txt extension\n");
                printf("Returning to main menu. Please try again.\n");
                return;
            }

            if(inLen > FILENAME_LEN)
            {
                printf("\nERROR: file name cannot be more than %d characters long\n", FILENAME_LEN);
                printf("Returning to main menu. Please try again.\n");
                return;
            }

            if(! isalpha(input[0]))
            {
                printf("\nERROR: file name should start with an english letter\n");
                printf("Returning to main menu. Please try again.\n");
                return;
            }

            for(int i = 0; i < 4; i++)
            {
                if(extention[i] != input[inLen-4+i])
                {
                    match = false;
                }
            }
            if(! match)
            {
                printf("\nERROR: file name should end in \".txt\"\n");
                printf("Returning to main menu. Please try again.\n");
                return;
            }

            for(int j = 0; j < inLen; j++)
            {
                if(input[j] == '.')
                {
                    count++;
                }

                if(input[j] == ' ')
                {
                    spaces++;
                }
            }
            if(count != 1)
            {
                printf("\nERROR: file name should contain exactly 1 period\n");
                printf("Returning to main menu. Please try again.\n");
                return;
            }
            if(spaces != 0)
            {
                printf("\nERROR: file name should contain 0 spaces\n");
                printf("Returning to main menu. Please try again.\n");
                return;
            }

            strncpy(name, input, FILENAME_LEN);

        }

        FILE* newFile = NULL;
        newFile = fopen(name, "r");
        if(newFile != NULL)
        {
            printf("ERROR: %s is the name of an existing calalog. Please choose a different name.\n", name);
            fclose(newFile);
        }
        else
        {
            exists = false;
        }

    }


    printf("\nYou will now add the first movie to your new catalog.\n");
    FILE* newfile = NULL;
    newfile = fopen(name, "w");

    Movie* firstMovie = NULL;
    char trash;
    scanf("%c", &trash);

    while(firstMovie == NULL)
        firstMovie = InsertToCatalog(database, firstMovie);
    fprintf(newfile, "1\n");
    PrintNodeToFile(firstMovie, newfile);

    fclose(newfile);

    int nextStep;
    int digit;
    bool loop = false;



    printf("\nFirst movie successfully added to your new catalog.\n\nWould you like to:\n(1) Continue with current catalog\n(2) Return to main menu\n");
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
            nextStep = digit;
            loop = CheckValidInput(1, 2, nextStep);
        }
    }
    if(nextStep == 1)
        UseCatalogMenu(database, name);

    return; // returns to Main Menu
}
