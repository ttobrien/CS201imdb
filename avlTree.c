//
// Created by tommy on 3/9/2019.
//

#include "avlTree.h"
#include "catalogs.h"

Movie* LoadDatabase()
{
    FILE *titleBasics = NULL;
    titleBasics = fopen("title.basics.tsv", "r");

    if(titleBasics == NULL)
    {
        printf("\ntitle.basics.tsv was not found\n\n");
        return NULL;
    }

    char tconst[15], titleType[15], primaryTitle[450], originalTitle[450], genres[GENRE_SPACE];
    char isAdult[3], startYear[NUM_SPACE], endYear[NUM_SPACE], runtimeMinutes[NUM_SPACE];
    char headers[20], trash;

    for(int i = 1; i <= 8; i++)
    {
        fscanf(titleBasics, "%s\t", headers);
    }
    fscanf(titleBasics, "%s", headers);

    Movie *tree = NULL;

    while(!feof(titleBasics))
    {
        fscanf(titleBasics, "%c", &trash);
        fscanf(titleBasics, " %s %[^\t] %[^\t] %[^\t] %s %s %s %s %[^\n]", tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres);

        if(strcmp(titleType,"movie") == 0)
        {
            tree = Insert(tree, ConvertToKey(primaryTitle), primaryTitle, genres, startYear, runtimeMinutes);
        }
    }
    fclose(titleBasics);

    return tree;
}

Movie* Insert(Movie *avl, char *nameKey, char *nameReg, char *types, char *yearStart, char *minutes)
{

    if(avl == NULL)
    {
        avl = (Movie *)malloc(sizeof(Movie));
        strcpy(avl->key, nameKey);
        strcpy(avl->title, nameReg);
        strcpy(avl->genre, types);
        strcpy(avl->year, yearStart);
        strcpy(avl->time, minutes);
        avl->left = NULL;
        avl->right = NULL;
    }

    else
    {
        if(strcmp(nameKey, avl->key) == 0)
            return avl;
        else if(strcmp(nameKey, avl->key) > 0)
        {
            avl->right = Insert(avl->right, nameKey, nameReg, types, yearStart, minutes);
            if(BF(avl) == -2)
            {
                if(strcmp(nameKey, avl->right->key) > 0)
                    avl = RR(avl);
                else
                    avl = RL(avl);
            }
        }
        else
        {
            avl->left = Insert(avl->left, nameKey, nameReg, types, yearStart, minutes);
            if(BF(avl) == 2)
            {
                if(strcmp(nameKey, avl->left->key) < 0)
                    avl = LL(avl);
                else
                    avl = LR(avl);
            }
        }
    }
    avl->height = height(avl);
    return avl;
}

void PrintInOrder(Movie *tree)
{
    if(tree == NULL)
        return;
    PrintInOrder(tree->left);
    printf("%s\n", tree->key);
    PrintInOrder(tree->right);
}

void PrintPreOrder(Movie* tree)
{
    if(tree == NULL)
        return;
    printf("%s\n", tree->key);
    PrintPreOrder(tree->left);
    PrintPreOrder(tree->right);
}


/*void LoadDatabase()
{
    FILE *titleBasics = NULL;
    titleBasics = fopen("title.basics.tsv", "r");

    if(titleBasics == NULL)//return NULL
    {
        printf("\ntitle.basics.tsv was not found\n\n");
        return;
    }

    char tconst[15], titleType[15], primaryTitle[50], originalTitle[50], genres[50];
    char isAdult[3], startYear[6], endYear[6], runtimeMinutes[6];
    char headers[20], trash;

    for(int i = 1; i <= 8; i++)
    {
        fscanf(titleBasics, "%s\t", headers);
    }
    fscanf(titleBasics, "%s", headers);

    Movie *tree = NULL;

    while(!feof(titleBasics))
    {
        fscanf(titleBasics, "%c", &trash);
        fscanf(titleBasics, " %s %[^\t] %[^\t] %[^\t] %s %s %s %s %[^\n]", tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres);

        //strcpy(another->title, primaryTitle);
        //strcpy(another->genre, genres);
        //strcpy(another->year, startYear);
        //strcpy(another->time, runtimeMinutes);
        //printf("\nTitle: %s\nGenres: %s\n Year: %s\nRuntime: %s\n", another->title, another->genre, another->year, another->time);

        if(strcmp(titleType,"movie") == 0)
        tree = Insert(tree, ConvertToKey(primaryTitle), primaryTitle, genres, startYear, runtimeMinutes);

    }
    fclose(titleBasics);

    return; //return tree

}*/

/*Movie* Insert(Movie *avl, char *nameKey, char *nameReg, char *types, char *yearStart, char *minutes)
{
    if(avl == NULL)
    {
        avl = (Movie *)malloc(sizeof(Movie));
        strcpy(avl->key, nameKey);
        strcpy(avl->title, nameReg);
        strcpy(avl->genre, types);
        strcpy(avl->year, yearStart);
        strcpy(avl->time, minutes);
        avl->left = NULL;
        avl->right = NULL;
    }

    else
    {
        if(strcmp(nameKey, avl->key) > 0)
        {
            avl->right = Insert(avl->right, nameKey, nameReg, types, yearStart, minutes);
            if(BF(avl) == -2)
            {
                if(strcmp(nameKey, avl->right->key) > 0)
                    avl = RR(avl);
                else
                    avl = RL(avl);
            }
        }
        else
        {
            avl->left = Insert(avl->left, nameKey, nameReg, types, yearStart, minutes);
            if(BF(avl) == 2)
            {
                if(strcmp(nameKey, avl->left->key) < 0)
                    avl = LL(avl);
                else
                    avl = LR(avl);
            }
        }
    }
    avl->height = height(avl);
    return avl;
}*/


int height(Movie *avl)
{
    int lh, rh;
    if(avl == NULL)
        return 0;

    if(avl->left == NULL)
        lh = 0;
    else
        lh = 1 + avl->left->height;

    if(avl->right == NULL)
        rh = 0;
    else
        rh = 1 + avl->right->height;

    if(lh > rh)
        return lh;
    return rh;
}

int BF(Movie *avl)
{
    int lh, rh;
    if(avl == NULL)
        return 0;

    if(avl->left == NULL)
        lh = 0;
    else
        lh = 1 + avl->left->height;

    if(avl->right == NULL)
        rh = 0;
    else
        rh = 1 + avl->right->height;

    return (lh - rh);
}

Movie *rotateRight(Movie *x)
{
    Movie *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = height(x);
    y->height = height(y);
    return y;
}

Movie *rotateLeft(Movie *x)
{
    Movie *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = height(x);
    y->height = height(y);
    return y;
}

Movie *RR(Movie *x)
{
    x = rotateLeft(x);
    return x;
}

Movie *LL(Movie *x)
{
    x = rotateRight(x);
    return x;
}

Movie *LR(Movie *x)
{
    x->left = rotateLeft(x->left);
    x = rotateRight(x);
    return x;
}

Movie *RL(Movie *x)
{
    x->right = rotateRight(x->right);
    x = rotateLeft(x);
    return x;
}

void SearchForMovie(Movie* database, char* titleKey, int keyLen, int count)
{
    if(database == NULL)
        return;
    else if(strncmp(database->key, titleKey, keyLen) == 0)
    {
        printf("%d: %s\n", database->title, ++count);
        SearchForMovie(database->left, titleKey, keyLen, count);
        SearchForMovie(database->right, titleKey, keyLen, count);
    }
    else if(strncmp(database->key, titleKey, keyLen) < 0)
    {
        SearchForMovie(database->right, titleKey, keyLen, count);
    }
    else
        SearchForMovie(database->left, titleKey, keyLen, count);
}









