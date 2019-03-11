//
// Created by tommy on 3/9/2019.
//

#ifndef CS201IMDB_AVLTREE_H
#define CS201IMDB_AVLTREE_H

#include <stdlib.h>
#include <string.h>

Movie* insert(Movie *, char *, char *, char *, int, int);
Movie* delete(Movie *, char *);
void preorder(Movie *);
void inorder(Movie *);
Movie* rotateRight(Movie *);
Movie *rotateLeft(MOvie *);
Movie *RR(Movie *);
Movie *LL(Movie *);
Movie *LR(Movie *);
Movie *RL(Movie *);
int BF(Movie *);
int height(Movie *);

#endif //CS201IMDB_AVLTREE_H
