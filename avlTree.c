//
// Created by tommy on 3/9/2019.
//

#include "avlTree.h"

#define TITLE_SPACE 50
#define GENRE_SPACE 50

typedef struct Movie
{
    char key[TITLE_SPACE];
    char title[TITLE_SPACE];
    char genre[GENRE_SPACE];
    int year;
    int time;
    Movie *left;
    Movie *right;
    int height;
} Movie;

Movie* Insert(Movie *avl, char *nameKey, char *nameReg, char *types, int yearStart, int minutes);
{
    if(avl == NULL)
    {
        avl = (Movie *)malloc(sizeof(Movie));
        strcpy(avl->key, nameKey);
        strcpy(avl->title, nameReg);
        strcpy(avl->genre, types);
        avl->year = yearStart;
        avl->time = minutes;
        avl->left = NULL;
        avl->right = NULL;
    }
    else
    {
        if(strcmp(nameKey, avl->key) > 0)
        {
            avl->right = insert(avl->right, nameKey, nameReg, types, yearStart, minutes);
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
            avl->left = insert(avl->left, nameKey, nameReg, types, yearStart, minutes);
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








