//
// Created by Tommy O'Brien on 3/7/2019.
//

#ifndef CS201IMDB_CATALOGS_H
#define CS201IMDB_CATALOGS_H

#include "libraries.h"
#include "avlTree.h"
#include "display.h"

/*
 * This is called when going to UseCatalogMenu. The user must input the name of a catalog that has already been made.
 * The function returns the name of the text file.
 */
char *EditCatalog();

/*
 * This function takes in either a full or partial movie title. The string is then converted to all lower case. If it
 * started with "a ", "the ", or "and ", then that substring will be appended to the end of the key with a comma and a
 * space. There is only one possible key that each entered string can map to. The keys are what is used to sort the
 * Movie structs in the AVL trees and what is checked when accessing one. The mapped key is returned.
 */
char *ConvertToKey(char *);

/*
 * This function takes in the name of a text file that is already an existing catalog. Then it reads in that file and
 * converts it back into an AVL tree of Movies. That tree is then returned.
 */
Movie* LoadCatalog(char *);

/*
 * This is the function that is called to start the process of adding a movie to a catalog. The first parameter is an
 * AVL tree of the entire database of movies, and the second is an AVL tree that represents the current working catalog.
 * It first calls SelectMovie to get the movie that the user wants to add. If that returns NULL the the original
 * catalog tree is returned. If a Movie struct is returned then it is inserted into the catalog tree and the user
 * chooses the media type and enters the date of acquisition. The updated tree of the catalog is the returned.
 */
Movie* InsertToCatalog(Movie *, Movie *);

/*
 * This function takes in the AVL tree that is storing the database of movies. First the user enters a partial movie
 * title. Then a list of all matching movie titles is printed by calling the recursive SearchForMovie function. Then
 * the user is prompted to enter the full exact title from the list above. This function returns a call to GetMovie and
 * passes it the database and the key for the full exact title.
 */
Movie* SelectMovie(Movie *);

/*
 * This function performs a O(lgn) search for the second parameter(the key for a movie) in the entire AVL tree of the
 * first parameter (the movie database). If the movie is found then it returns that node, but if not NULL is returned.
 */
Movie* GetMovie(Movie *, char *);

/*
 * This function takes in the working catalog of movies and prints out all of the movies and all of their individual
 * information to the screen.
 */
void PrintAll(Movie *);

/*
 * The first parameter is the AVL tree for the current catalog. The second parameter is a file pointer for the catalog.
 * It recursively performs an in-order traversal to print all of the information for each movie in the tree. Each movie
 * is printed on its own line and each piece of data is separated by a tab.
 */
void PrintNodeToFile(Movie *, FILE *);

/*
 * This function takes in the working catalog of movies as the first parameter and the key for a Movie struct as the
 * second parameter. It performs an O(lgn) search and prints out all of information for that struct  to the screen.
 */
void PrintOneMovie(Movie *, char *);


#endif //CS201IMDB_CATALOGS_H
