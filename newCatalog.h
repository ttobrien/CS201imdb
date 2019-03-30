//
// Created by Tommy O'Brien on 3/7/2019.
//

#ifndef CS201IMDB_NEWCATALOG_H
#define CS201IMDB_NEWCATALOG_H

#include "avlTree.h"

/*
 * This function is passed the database AVL tree of all IMDb movies. First, the user is asked for a name for this
 * new catalog. The name is then checked for validity and that it includes the .txt extension. Then it adds the first
 * movie to this catalog, and prints it to the text file with the previously entered name. At the end, the user can
 * continue using the catalog or return to the main menu.
 */
void NewCatalog(Movie *);

#endif //CS201IMDB_NEWCATALOG_H
