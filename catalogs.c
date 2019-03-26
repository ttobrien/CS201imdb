//
// Created by tommy on 3/7/2019.
//

#include "catalogs.h"


char* EditCatalog()
{
    char* name;
    name = (char *)malloc(NAME_LEN * sizeof(char));
    bool exists = false;
    while(!exists)
    {
        printf("What is the name of the catalog would you like to edit: ");
        scanf("%s", name);
        FILE* catalogName = NULL;
        catalogName = fopen(name, "r");
        if (catalogName == NULL)
            printf("%s does not exist. Try again.\n", name);
        else
            exists = true;
    }
    return name;
}


char* ConvertToKey(char* title)
{
    int len = strlen(title);
    char* temp;
    char* key;
    temp = (char *)malloc((len+1)*sizeof(char));
    key = (char *)malloc((len+2)*sizeof(char));


    for(int i = 0; i < len; i++)
    {
        temp[i] = tolower(title[i]);
    }

    if(strncmp(temp, "the ", 4) == 0)
    {

        for(int i = 4; i < len; i++)
        {
            key[i-4] = temp[i];
        }

        strcat(key, ", the\0");
    }

    else if(strncmp(temp, "a ", 2) == 0)
    {
        for(int i = 2; i < len; i++)
        {
            key[i-2] = temp[i];
        }

        strcat(key, ", a\0");
    }

    else if(strncmp(temp, "and ", 4) == 0)
    {
        for(int i = 4; i < len; i++)
        {
            key[i-4] = temp[i];
        }

        strcat(key, ", and\0");
    }

    else
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
    fscanf(catalogName, "%d\n", &movieSignal);

    while(!feof(catalogName))
    {
        fscanf(catalogName, " %[^\t] %[^\t] %[^\t] %s %s %s %[^\n]", key, primaryTitle, genres, startYear, runtimeMinutes, mediaType, dateAcquired);
        catalogTree = Insert(catalogTree, key, primaryTitle, genres, startYear, runtimeMinutes);
        catalogTree = UpdateMediaType(catalogTree, key, mediaType);
        catalogTree = UpdateDate(catalogTree, key, dateAcquired);
    }

    fclose(catalogName);

    return catalogTree;
}

Movie* SelectMovie(Movie *database)
{
    char* titleKey;
    char title[TITLE_SPACE];
    printf("Enter name of movie that you would like to add to your catalog: ");
    scanf(" %[^\n]", title);
    //fgets(title, TITLE_SPACE, stdin);
    //strcpy(title, DeleteNewlineCharAtEnd(title));
    titleKey = ConvertToKey(title);
    int len = strlen(titleKey);
    SearchForMovie(database, titleKey, len);
    printf("Enter full title of movie from above list: ");
    scanf(" %[^\n]", title);
    strcpy(titleKey, ConvertToKey(title));
    printf("The key for whatt you entered: (%s)\n", titleKey);
    //fgets(title, TITLE_SPACE, stdin);
    //strcpy(title, DeleteNewlineCharAtEnd(title));
    return GetMovie(database, titleKey);
    //return GetMovie(database, ConvertToKey(title));

}

char* DeleteNewlineCharAtEnd(char *str)
{
    int len = strlen(str);
    str[len-1] = '\0';
    return str;
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
    if(movieToInsert == NULL)
    {
        printf("No movies found containing the entered string.\n");
        //printf("Note that movies beginning with: \"A\", \"Le\", \"The\", have had those substrings appended to the end of the title with a comma.");
        return catalogTree;
    }
    catalogTree = Insert(catalogTree, movieToInsert->key, movieToInsert->title, movieToInsert->genre, movieToInsert->year, movieToInsert->time);
    catalogTree = InitializeMediaTypeMenu(catalogTree, movieToInsert->key);
    catalogTree = InitializeDateMenu(catalogTree, movieToInsert->key);
    return catalogTree;

}

void PrintAll(Movie *catalogTree)
{
    if (catalogTree == NULL)
    {
        return;
    }
    PrintAll(catalogTree->left);
    printf("Movie: %s\nGenre(s): %s\nRelease Year: %s\nRuntime: %s minutes\nMedia Type: %s\nDate Acquired: %s", catalogTree->title, catalogTree->genre, catalogTree->year, catalogTree->time, catalogTree->media, catalogTree->date);
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
