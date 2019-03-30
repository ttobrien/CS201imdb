//
// Created by Tommy O'Brien on 3/7/2019.
//

#include "newCatalog.h"
#include "display.h"
#include "libraries.h"
#include "catalogs.h"




void NewCatalog(Movie *database)
{
    char name[FILENAME_LEN];//stores potential file names
    char input[INPUT_LEN];  //stores user input
    bool exists = true;     //keeps loop going until new, valid file name is entered
    int inLen;              //length of inputted string
    char extension[10];     //used for checking the .txt extension in input
    bool match = true;      //turned false if input doesnt end in .txt
    int count = 0;          //counts '.' in input
    int spaces = 0;         //counts spaces in input

    while(exists)
    {
        spaces = 0; //resets variables
        count = 0;
        match = true;
        
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
            strcpy(extension, ".txt");

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

            if(! isalpha(input[0]))     //stricter than normal naming conventions to make naming simpler
            {
                printf("\nERROR: file name should start with an english letter\n");
                printf("Returning to main menu. Please try again.\n");
                return;
            }

            for(int i = 0; i < 4; i++)  //checks that .txt are the last four characters of the input string
            {
                if(extension[i] != input[inLen-4+i])
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

            for(int j = 0; j < inLen; j++)  //no spaces and only 1 '.' (for .txt) allowed to make naming simpler and avoid any weird potential behavior with files
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

        FILE* newFile = NULL;       //checks if file name is already a catalog in the folder
        newFile = fopen(name, "r");
        if(newFile != NULL)
        {
            printf("ERROR: %s is the name of an existing catalog. Please choose a different name.\n", name);
            fclose(newFile);
        }
        else
        {
            exists = false; //if it is a new name then the loop is broken and the name for the catalog is used
        }

    }


    printf("\nYou will now add the first movie to your new catalog.\n");
    FILE* newfile = NULL;
    newfile = fopen(name, "w");

    Movie* firstMovie = NULL;
    char trash;
    scanf("%c", &trash);

    while(firstMovie == NULL)   //forces user to add movie to catalog
        firstMovie = InsertToCatalog(database, firstMovie);
    fprintf(newfile, "1\n");    //saving the new catalog with the just added movie
    PrintNodeToFile(firstMovie, newfile);

    fclose(newfile);

    int nextStep;
    int digit;
    bool loop = false;



    printf("\n\nWould you like to:\n(1) Continue with current catalog\n(2) Return to main menu\n");
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
