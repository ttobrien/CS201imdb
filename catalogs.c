//
// Created by Tommy O'Brien on 3/7/2019.
//

#include "catalogs.h"


char* EditCatalog()
{
    char* name; //catalog's file name
    name = (char *)malloc(FILENAME_LEN * sizeof(char));

    char input[INPUT_LEN];
    bool exists = false;

    while(!exists)  //terminates once name of an exiting catalog is inputted
    {
        printf("\nWhat is the name of the catalog would you like to edit: ");
        scanf(" %250[^\n]", input);
        if(strlen(input) == INPUT_LEN)
        {
            printf("\nERROR: Maximum input length exceeded. Program closing. Current data for the current catalog might have been lost.\n");
            exit(1);
        }
        strncpy(name, input, FILENAME_LEN); //prevents overflowing name
        FILE* catalogName = NULL;
        catalogName = fopen(name, "r");
        if (catalogName == NULL)
            printf("%s does not exist. Try again.\n", name);
        else
        {
          fclose(catalogName);
          exists = true;
        }


    }
    return name;
}


char* ConvertToKey(char* title)
{
    int len = strlen(title);
    if((len + 2) >= TITLE_SPACE)    //restricts input for title to 248 to avoid potentially overflowing the key when returned
    {
        printf("\nERROR: while converting the entered title into its key the maximum length would have been exceeded.\nProgram closing. Current data for the current catalog might have been lost.\n");
        exit(1);
    }
    char* temp;
    char* key;
    temp = (char *)malloc((len+1)*sizeof(char));
    key = (char *)malloc((len+2)*sizeof(char));     //for when title starts with "a", "and", or "the"

    for(int i = 0; i < len; i++)
    {
        temp[i] = tolower(title[i]);
    }

    if(strncmp(temp, "the ", 4) == 0)  //appends "the" to end with a comma
    {

        for(int i = 4; i < len; i++)
        {
            key[i-4] = temp[i];
        }

        key[len-4] = ',';
        key[len-3] = ' ';
        key[len-2] = 't';
        key[len-1] = 'h';
        key[len] = 'e';
        key[len+1] = '\0';
    }


    else if(strncmp(temp, "a ", 2) == 0)  //appends "a" to end with a comma
    {
        for(int i = 2; i < len; i++)
        {
            key[i-2] = temp[i];
        }

        key[len-2] = ',';
        key[len-1] = ' ';
        key[len] = 'a';
        key[len+1] = '\0';
    }

    else if(strncmp(temp, "and ", 4) == 0) //appends "and" to end with a comma
    {
        for(int i = 4; i < len; i++)
        {
            key[i-4] = temp[i];
        }

        key[len-4] = ',';
        key[len-3] = ' ';
        key[len-2] = 'a';
        key[len-1] = 'n';
        key[len] = 'd';
        key[len+1] = '\0';
    }

    else    //lowercase version of title is returned to be the key
    {
        temp[len] = '\0';
        return temp;
    }
    return key;
}

Movie* LoadCatalog(char* name)
{
    FILE* catalogName = NULL;
    catalogName = fopen(name, "r");
    if(catalogName == NULL)
    {
        printf("Catalog %s does not exists.\n", name);
        return NULL;
    }

    char key[TITLE_SPACE], primaryTitle[TITLE_SPACE], genres[GENRE_SPACE], startYear[NUM_SPACE], runtimeMinutes[NUM_SPACE], mediaType[10], dateAcquired[15];
    Movie *catalogTree = NULL;
    int movieSignal;
    fscanf(catalogName, "%d\n", &movieSignal);  //reads in the '0' or '1' of the top line of the file

    while(!feof(catalogName))   //creating AVL tree out of catalog's file
    {
        fscanf(catalogName, " %[^\t] %[^\t] %[^\t] %s %s %s %[^\n]", key, primaryTitle, genres, startYear, runtimeMinutes, mediaType, dateAcquired);
        catalogTree = Insert(catalogTree, key, primaryTitle, genres, startYear, runtimeMinutes);
        catalogTree = UpdateMediaType(catalogTree, key, mediaType);
        catalogTree = UpdateDate(catalogTree, key, dateAcquired);
    }

    fclose(catalogName);

    return catalogTree;
}

Movie* SelectMovie(Movie *database) //strncpy and strncmp
{
    char* titleKey1;    //1 and 2 are used to distinguish first and second parts of process for selecting a movie
    char* titleKey2;
    char title1[TITLE_SPACE];
    char input1[INPUT_LEN];
    char title2[TITLE_SPACE];
    char input2[INPUT_LEN];
    printf("\nEnter name of movie that you would like to add to your catalog: ");
    scanf(" %250[^\n]", input1);
    if(strlen(input1) == INPUT_LEN)
    {
        printf("\nERROR: Maximum input length exceeded. Program closing. Current data for the current catalog might have been lost.\n");
        exit(1);
    }
    strcpy(title1, input1);  //TITLE_SPACE = INPUT_LEN
    titleKey1 = ConvertToKey(title1);
    int len = strlen(titleKey1);
    printf("\nThe following movie(s) fully match or start with the entered string:\n\n");
    SearchForMovie(database, titleKey1, len);
    printf("\nEnter full title of movie exactly as it appears in the list above: ");
    scanf(" %250[^\n]", input2);
    if(strlen(input2) == INPUT_LEN)
    {
        printf("\nERROR: Maximum input length exceeded. Program closing. Current data for the current catalog might have been lost.\n");
        exit(1);
    }
    strcpy(title2, input2);   //TITLE_SPACE = INPUT_LEN
    titleKey2 = ConvertToKey(title2);
    return GetMovie(database, titleKey2);
}

Movie* GetMovie(Movie *database, char *movieTitle)
{
    if(database == NULL)
        return NULL;

    else if(strcmp(database->key, movieTitle) == 0) //else if(strcmp(database->key, movieTitle) == 0)
    {
        return database;
    }
    else if(strcmp(database->key, movieTitle) < 0) //else if(strcmp(database->key, movieTitle) < 0)
    {
        return GetMovie(database->right, movieTitle);
    }
    else
        return GetMovie(database->left, movieTitle);

}

Movie* InsertToCatalog(Movie *database, Movie *catalogTree)
{
    Movie* movieToInsert = SelectMovie(database);
    if(movieToInsert == NULL)   //GetMovie returned NULL
    {
        printf("\nNo movies found containing the entered string. Nothing added to catalog\n");
        return catalogTree;
    }

    catalogTree = Insert(catalogTree, movieToInsert->key, movieToInsert->title, movieToInsert->genre, movieToInsert->year, movieToInsert->time);
    catalogTree = InitializeMediaTypeMenu(catalogTree, movieToInsert->key);
    catalogTree = InitializeDateMenu(catalogTree, movieToInsert->key);
    printf("\nMovie successfully added.\n");
    return catalogTree;

}

void PrintOneMovie(Movie *catalogTree, char *movieKey)
{
    if(catalogTree == NULL)
    {
        printf("\nMovie not found.\n");
        return;
    }

    else if(strcmp(catalogTree->key, movieKey) == 0)
    {
        printf("\nMovie: %s\nGenre(s): %s\nRelease Year: %s\nRuntime: %s minutes\nMedia Type: %s\nDate Acquired: %s\n\n", catalogTree->title, catalogTree->genre, catalogTree->year, catalogTree->time, catalogTree->media, catalogTree->date);

        return;
    }
    else if(strcmp(catalogTree->key, movieKey) < 0) //else if(strcmp(database->key, movieTitle) < 0)
    {
        PrintOneMovie(catalogTree->right, movieKey);
    }
    else
        PrintOneMovie(catalogTree->left, movieKey);

}


void PrintAll(Movie *catalogTree)
{
    if (catalogTree == NULL)
    {
        return;
    }
    PrintAll(catalogTree->left);
    printf("Movie: %s\nGenre(s): %s\nRelease Year: %s\nRuntime: %s minutes\nMedia Type: %s\nDate Acquired: %s\n\n", catalogTree->title, catalogTree->genre, catalogTree->year, catalogTree->time, catalogTree->media, catalogTree->date);
    PrintAll(catalogTree->right);
}

void PrintNodeToFile(Movie *catalogTree, FILE *writeFile)
{
    if(catalogTree == NULL)
    {
        return;
    }
    PrintNodeToFile(catalogTree->left, writeFile);
    fprintf(writeFile, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", catalogTree->key, catalogTree->title, catalogTree->genre, catalogTree->year, catalogTree->time, catalogTree->media, catalogTree->date);
    PrintNodeToFile(catalogTree->right, writeFile);
}
