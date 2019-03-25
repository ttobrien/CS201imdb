//
// Created by tommy on 3/7/2019.
//

#ifndef CS201IMDB_CATALOGS_H
#define CS201IMDB_CATALOGS_H

#include "libraries.h"
#include "avlTree.h"
#include "display.h"

char *EditCatalog();
char *ConvertToKey(char *);
Movie* LoadCatalog(char *);
Movie* InsertToCatalog(Movie *, Movie *);
Movie* SelectMovie(Movie *);
Movie* GetMovie(Movie *, char *);
void PrintAll(Movie *);
void PrintNodeToFile(Movie *, FILE *);
char* DeleteNewlineCharAtEnd(char *);


#endif //CS201IMDB_CATALOGS_H
