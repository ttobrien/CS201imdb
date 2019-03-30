//
// Created by Tommy O'Brien on 3/7/2019.
//

#ifndef CS201IMDB_DISPLAY_H
#define CS201IMDB_DISPLAY_H

#include "libraries.h"
#include "avlTree.h"

/*
 * This function prints the opening messages. Then it calls LoadDatabase() to create the AVL Tree of all Movies.
 * This returns whatever is returned from LoadDatabase().
 */
Movie* StartUp();

/*
 * This program prints a menu that gives the user the choice between creating a new catalog, editing an existing
 * catalog, or closing the program. Then it proceeds to follow the requested action.
 */
int MainMenu();

/*
 * The first integer passed to this function is the inclusive lower bound on acceptable input. The second integer
 * is the inclusive upper bound on acceptable input. The third integer is the number that was entered. This function
 * is good for checking that a number is in range. It is used several times throughout this project to verify menu
 * selection choices. The function returns true if the input is in range, and false if it is not.
 */
bool CheckValidInput(int, int, int);

/*
 * In order, the parameters are: the AVL tree of all IMDB Movies and the name of the catalog in use. First it turns the
 * catalog's text file into an AVL tree of Movies. Then the user is put into a loop where he or she can perform multiple
 * actions on the catalog's tree. These actions include: adding a movie, removing a movie, updating a movies media type
 * or date of acquisition, viewing information for a specific movie, or viewing all information for all movies. When
 * '7' is entered as the menu screen, the loop is exited, the catalog information is written to the text file of the
 * name that was passed in, and the user is returned back to the main menu.
 */
void UseCatalogMenu(Movie*, char*);

/*
 * The parameter is a string that was inputted. This function checks to make sure that the string is of length 1 and
 * that one character is a digit (0-9). If the above specifications are not met then -1 is returned, but if they are
 * the passed in digit is returned.
 */
int CheckInputIsDigit(char *);

/*
 * In order, its parameters are: an AVL Tree of Movies in the catalog in use and the key for the movie to be updated.
 * The user enters a movie title of one in the catalog and can choose between the media types of dvd, bluray, and
 * digital. Then UpdateMediaType is called. The function returns the AVL tree that is returned from UpdateMediaType.
 */
Movie *InitializeMediaTypeMenu(Movie *, char *);

/*
 * In order, its parameters are: an AVL Tree of Movies in the catalog in use and the key for the movie to be updated.
 * The user enters a date in the form of MM/DD/YYYY. Then UpdateDate is called. The function returns the AVL tree that
 * is returned from UpdateDate.
 */
Movie *InitializeDateMenu(Movie *, char *);

/*
 * In order, its parameters are: an AVL Tree of Movies in the catalog in use , the catalog's name, and the action being
 * performed. This function is called several times from UseCatalogMenu. A message about entering a title to perform
 * the action passed in on is printed. The user enters a title and if it doesnt meet or exceed 250 characters then it
 * is returned. However, if there were too many characters entered then the program saves the current catalog
 * information to the text file corresponding to the catalog name that was passed in and shuts down the program.
 */
char *GetTitleToUse(Movie *, char *, char *);

#endif //CS201IMDB_DISPLAY_H
