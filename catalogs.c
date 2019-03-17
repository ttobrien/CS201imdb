//
// Created by tommy on 3/7/2019.
//

#include "catalogs.h"
#include "libraries.h"

void EditCatalog()
{
    int choice = EditMenu();
    return;
}

char *SelectCatalog()
{
    char name[NAME_LEN];
    int exists;

    printf("Enter name of catalog: ");
    scanf("%s", name);
    exists = CatalogExists(name);

    if(exists == 1)


}

int CatalogExists(char *name)
{

}

char* ConvertToKey(char* title)
{
    int len = strlen(title);
    char* temp;
    char* key;
    temp = (char *)malloc(len*sizeof(char));
    key = (char *)malloc((len+1)*sizeof(char));


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

        strcat(key, ", the");
    }

    else if(strncmp(temp, "a ", 2) == 0)
    {
        for(int i = 2; i < len; i++)
        {
            key[i-2] = temp[i];
        }

        strcat(key, ", a");
    }

    else if(strncmp(temp, "le ", 3) == 0)
    {
        for(int i = 3; i < len; i++)
        {
            key[i-3] = temp[i];
        }

        strcat(key, ", le");
    }

    else
        return temp;


    return key;
}

