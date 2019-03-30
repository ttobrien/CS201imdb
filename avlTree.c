//
// Created by Tommy O'Brien on 3/9/2019.
//

#include "avlTree.h"
#include "catalogs.h"

Movie* LoadDatabase()
{
    FILE *titleBasics = NULL;
    titleBasics = fopen("title.basics.tsv", "r"); //file with all of the movie information

    if(titleBasics == NULL)
    {
        printf("\ntitle.basics.tsv was not found\n\n");
        return NULL;
    }

    char tconst[15], titleType[15], primaryTitle[450], originalTitle[450], genres[GENRE_SPACE];
    char isAdult[3], startYear[NUM_SPACE], endYear[NUM_SPACE], runtimeMinutes[NUM_SPACE];
    char headers[20], trash;

    for(int i = 1; i <= 8; i++)     //reads in top line of categories
    {
        fscanf(titleBasics, "%s\t", headers);
    }
    fscanf(titleBasics, "%s", headers);

    Movie *tree = NULL;

    while(!feof(titleBasics))   //this loop adds everything designated as a movie into the AVL tree
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

Movie* Insert(Movie *avl, char *nameKey, char *nameReg, char *types, char *yearStart, char *minutes) //see citation in header file
{

    if(avl == NULL) //inserting Movie as a leaf in the correct ordering position
    {
        avl = (Movie *)malloc(sizeof(Movie));
        strcpy(avl->key, nameKey);
        strcpy(avl->title, nameReg);
        strcpy(avl->genre, types);
        strcpy(avl->year, yearStart);
        strcpy(avl->time, minutes);
        strcpy(avl->date, "empty");
        strcpy(avl->media, "empty");
        avl->left = NULL;
        avl->right = NULL;
    }

    else
    {
        if(strcmp(nameKey, avl->key) == 0)  //duplicate titles/keys are not allowed
            return avl;
        else if(strcmp(nameKey, avl->key) > 0)
        {
            avl->right = Insert(avl->right, nameKey, nameReg, types, yearStart, minutes);
            if(BF(avl) == -2)   //ensuring AVL property as recursion unfolds back up the tree
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
            if(BF(avl) == 2)    //ensuring AVL property as recursion unfolds back up the tree
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

Movie* Remove(Movie *avl, char *name)   //see citation in header file
{
    Movie *temp;    //needed when removing a match

    if(avl == NULL)
    {
        printf("\nTitle not found. Movie not removed. Before trying again, view all movies in your catalog with option 6.\n");
        return NULL;
    }
    else
    {
        if(strcmp(name, avl->key) > 0)
        {
            avl->right = Remove(avl->right, name);
            if(BF(avl) == 2)    //ensuring AVL property as recursion unfolds back up the tree
            {
                if(BF(avl->left) >= 0)
                {
                    avl = LL(avl);
                }
                else
                {
                    avl = LR(avl);
                }
            }
        }
        else if(strcmp(name, avl->key) < 0)
        {
            avl->left = Remove(avl->left, name);
            if(BF(avl) == -2)   //ensuring AVL property as recursion unfolds back up the tree
            {
                if(BF(avl->right) <= 0)
                {
                    avl = RR(avl);
                }
                else
                {
                    avl = RL(avl);
                }
            }
        }
        else
        {
            if(avl->right != NULL)
            {
                temp = avl->right;  //finding successor
                while(temp->left != NULL)
                {
                    temp = temp->left;
                }
                strcpy(avl->key, temp->key);    //essentially switching nodes
                strcpy(avl->title, temp->title);
                strcpy(avl->year, temp->year);
                strcpy(avl->time, temp->time);
                strcpy(avl->genre, temp->genre);
                strcpy(avl->media, temp->media);
                strcpy(avl->date, temp->date);

                avl->right = Remove(avl->right, temp->key);
                if(BF(avl) == 2)    //ensuring AVL property
                {
                    if(BF(avl->left) >= 0)
                    {
                        avl = LL(avl);
                    }
                    else
                    {
                        avl = LR(avl);
                    }
                }
            }
            else
            {
                temp = avl->left;   //Movie to remove is replaced by its left child
                return temp;
            }
        }
    }

    avl->height = height(avl);
    return avl;
}

Movie* UpdateMediaType(Movie *avl, char *nameKey, char *mediaType)
{

    if(avl == NULL)  //reached NULL leaf location along path where nameKey's movie should have existed somewhere in, so the title is not in the tree
    {
        printf("\nERROR: Movie not found. Media type not added.\n");
        return NULL;
    }

    else
    {
        if(strcmp(nameKey, avl->key) == 0)      //movie found and date is updated
        {
            strcpy(avl->media, mediaType);
            return avl;
        }
        else if(strcmp(nameKey, avl->key) > 0)
        {
            avl->right = UpdateMediaType(avl->right, nameKey, mediaType);
        }
        else
        {
            avl->left = UpdateMediaType(avl->left, nameKey, mediaType);
        }
    }
    return avl;
}

Movie* UpdateDate(Movie *avl, char *nameKey, char *dateAcquired)
{

    if(avl == NULL)  //reached NULL leaf location along path where nameKey's movie should have existed somewhere in, so the title is not in the tree
    {
        printf("\nERROR: Movie not found. Date of acquisition not added.\n");
        return NULL;
    }

    else
    {
        if(strcmp(nameKey, avl->key) == 0)      //movie found and date is updated
        {
            strcpy(avl->date, dateAcquired);
            return avl;
        }
        else if(strcmp(nameKey, avl->key) > 0)
        {
            avl->right = UpdateDate(avl->right, nameKey, dateAcquired);
        }
        else
        {
            avl->left = UpdateDate(avl->left, nameKey, dateAcquired);
        }
    }
    return avl;
}

int height(Movie *avl)  //see citation in header file
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

    if(lh > rh)     //return length of longest path to NULL leaf
        return lh;
    return rh;
}

int BF(Movie *avl)  //see citation in header file
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

    return (lh - rh); //difference in height between left and right children
}

Movie *rotateRight(Movie *x)    //see citation in header file
{
    Movie *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = height(x);
    y->height = height(y);
    return y;
}

Movie *rotateLeft(Movie *x)     //see citation in header file
{
    Movie *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = height(x);
    y->height = height(y);
    return y;
}

Movie *RR(Movie *x)         //see citation in header file
{
    x = rotateLeft(x);
    return x;
}

Movie *LL(Movie *x)         //see citation in header file
{
    x = rotateRight(x);
    return x;
}

Movie *LR(Movie *x)         //see citation in header file
{
    x->left = rotateLeft(x->left);
    x = rotateRight(x);
    return x;
}

Movie *RL(Movie *x)         //see citation in header file
{
    x->right = rotateRight(x->right);
    x = rotateLeft(x);
    return x;
}

void SearchForMovie(Movie* database, char* titleKey, int keyLen)
{
    if(database == NULL)
        return;
    else if(strncmp(database->key, titleKey, keyLen) == 0) //when a movie matches, it is possible that subsequent movies to the left or right in its subtree could match
    {
        SearchForMovie(database->left, titleKey, keyLen);
        printf("%s\n", database->title);
        SearchForMovie(database->right, titleKey, keyLen);
    }
    else if(strncmp(database->key, titleKey, keyLen) < 0)
    {
        SearchForMovie(database->right, titleKey, keyLen);
    }
    else
        SearchForMovie(database->left, titleKey, keyLen);
}
