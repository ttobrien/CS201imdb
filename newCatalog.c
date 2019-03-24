//
// Created by tommy on 3/7/2019.
//

#include "newCatalog.h"
#include "display.h"
#include "libraries.h"
#include "catalogs.h"



void NewCatalog(Movie *database)
{
    char name[NAME_LEN];
    bool exists = true;
    char existingName[NAME_LEN];
    int nameCount;
    int nameMatch;

    while(exists)
    {
        nameCount = 0;
        nameMatch = 0;

        printf("\nWhat would you like to name this catalog? ");
        scanf("%s", name);

        FILE *namesFile = NULL;
        namesFile = fopen("CatalogNames", "r");
        if(namesFile == NULL)
        {
            exists = false;
        }
        else
        {
            while( ! feof(namesFile) )
            {
                nameCount++;
                fscanf(namesFile, "%s\n", existingName);
                if(strcmp(existingName, name) == 0)
                {
                    nameMatch++;
                }
            }
            if(nameMatch == 0)
            {
                exists = false;
            }
        }
        fclose(namesFile);

        if(exists)
        {
            printf("\nError: %s is the name of an existing catalog. Please choose a different name.\n", name);
        }
        else
        {

            if(nameCount == 0)
            {
                namesFile = fopen("CatalogNames", "w");
                fprintf(namesFile, "%s\n", name);
                fclose(namesFile);
            }
            else
            {
                namesFile = fopen("CatalogNames", "r");
                char nameList[nameCount + 1][NAME_LEN];
                for(int i = 0; i < nameCount; i++)
                {
                    fscanf(namesFile, "%s\n", nameList[i]);
                }
                strcpy(nameList[nameCount], name);
                fclose(namesFile);

                namesFile = fopen("CatalogNames", "w");
                for(int i = 0; i <=nameCount; i++)
                {
                    fprintf(namesFile, "%s\n", nameList[i]);
                }
                fclose(namesFile);
            }
        }
    }



    printf("You will now add the first movie to your new catalog.\n");
    FILE* newfile = NULL;
    newfile = fopen(name, "w");

    Movie* firstMovie = NULL;
    char trash;
    scanf("%c", &trash);

    while(firstMovie == NULL)
        firstMovie = InsertToCatalog(database, firstMovie);
    PrintNodeToFile(firstMovie, newfile);

    fclose(newfile);


    int nextStep;
    bool loop = false;



    printf("\nFirst movie successfully added to your new catalog.\n\nWould you like to:\n(1) Continue with current catalog\n(2) Return to main menu\n");
    while(! loop)
    {
        printf("\nEnter number of choice: ");
        scanf("%d", &nextStep);
        loop = CheckValidInput(1, 2, nextStep);
    }
    if(nextStep == 1)
        UseCatalogMenu(database, name);
    else
        //MainMenu
    return;
}


