all:
	gcc -Wall -std=c11 main.c avlTree.c catalogs.c newCatalog.c display.c -o imdb
