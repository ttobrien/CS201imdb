//
// Created by tommy on 3/9/2019.
//

#ifndef CS201IMDB_AVLTREE_H
#define CS201IMDB_AVLTREE_H

#include "libraries.h"

#define TITLE_SPACE 250
#define GENRE_SPACE 50
#define NUM_SPACE 10

typedef struct Movie
{
    char key[TITLE_SPACE];
    char title[TITLE_SPACE];
    char genre[GENRE_SPACE];
    char year[NUM_SPACE];
    char time[NUM_SPACE];
    char media[10];
    char date[15];
    struct Movie *left;
    struct Movie *right;
    int height;
} Movie;


/*
 * Reads in each movie in title.basics.tsv into the Movie struct. Each struct is added into the AVL tree.
 * The complete AVL tree of all movies in the file is returned to be the database the the program will use.
 */
Movie* LoadDatabase();

/*
 * In order, its parameters are: an AVL tree of Movies, the key for the movie, the movie's official title,
 * the year the movie was released, and the runtime of the movie in minutes. The function creates a new movie
 * from the information passed and places it into the correct position of the AVL tree based off of the key
 * that was passed. If there already exists a movie with the same key (i.e. title) then the passed information
 * will not be added. It returns the full updated tree.
 * See citation below.
 */
Movie* Insert(Movie *, char *, char *, char *, char *, char *);

/*
 * In order, its parameters are: an AVL tree of Movies and the key for the movie to be deleted. If there is a matching
 * key in the AVL tree, then that movie is removed from the tree. When necessary the AVL tree will automatically
 * balance itself. It returns the full updated tree.
 * See citation below.
 */
Movie* Remove(Movie *, char *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. A right rotation is performed on the root of that subtree.
 * It returns the updated subtree.
 * See citation below.
 */
Movie* rotateRight(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. A left rotation is performed on the root of that subtree.
 * It returns the updated subtree.
 * See citation below.
 */
Movie *rotateLeft(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. A left rotation is performed on the root of that subtree.
 * It returns the updated subtree.
 * See citation below.
 */
Movie *RR(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. A right rotation is performed on the root of that subtree.
 * It returns the updated subtree.
 * See citation below.
 */
Movie *LL(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. A left rotation is performed on the left child of the root
 * of that subtree. Then a right rotation is performed on the root. It returns the updated subtree.
 * See citation below.
 */
Movie *LR(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. A right rotation is performed on the right child of the root
 * of that subtree. Then a left rotation is performed on the root. It returns the updated subtree.
 * See citation below.
 */
Movie *RL(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. Calculations are performed to determine the difference of
 * heights of the roots left and right children's subtrees. This is called to check that the height differential is not
 * greater than 1 or less than -1. The difference of heights ir returned.
 * See citation below.
 */
int BF(Movie *);

/*
 * The parameter is a pointer to a subtree of an AVL tree. It returns the height of the root.
 * See citation below.
 */
int height(Movie *);

/*
 * In order, its parameters are: an AVL Tree of Movies, the key for the movie that is wanted to be updated, and the
 * new media type. If there is a matching key in the tree, then that node's media type is updated to the new media type
 * that was passed in. It returns the full updated tree.
 */
Movie* UpdateMediaType(Movie *, char *, char *);

/*
 * In order, its parameters are: an AVL Tree of Movies, the key for the movie that is wanted to be updated, and the
 * new date. If there is a matching key in the tree, then that node's date is updated to the new date
 * that was passed in. It returns the full updated tree.
 */
Movie* UpdateDate(Movie *, char *, char *);

/*
 * In order, its parameters are: an AVL Tree of Movies, a partial movie title key that is being searched for, and the length
 * of the partial title. The entire AVL tree is searched with a pre-order traversal, and whenever the first whatever the
 * passed int is characters of a movie's key matches the partial key that was passed, the movie's title is printed to the screen.
 */
void SearchForMovie(Movie *, char *, int);


/*
 * CITATION: All noted functions above were modified from Neeraj Mishra's "Program for AVL Tree in C"
 * https://www.thecrazyprogrammer.com/2014/03/c-program-for-avl-tree-implementation.html
 */


#endif //CS201IMDB_AVLTREE_H
