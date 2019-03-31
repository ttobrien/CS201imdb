//
// Created by Tommy O'Brien on 3/7/2019.
//

#include "libraries.h"
#include "display.h"
#include "newCatalog.h"
#include "catalogs.h"
#include "avlTree.h"


int main(void)
{
    Movie *tree = StartUp(); //Does introductory output and creates and stores the avl Tree from the IMDb data file

    if(tree == NULL) //Program closes if datafile is not found since there is not much a user could do without the database
    {
        printf("Database not loaded. Exiting program.\n\n");
        return 0;
    }

    while(1) //functionality to close program is available and will need repeated use of this until program termination so infinite loop is good
    {

        int choice = MainMenu();
        switch (choice)
        {
            case 1 :    //User will create a new catalog, add one movie to it, and then choose to continue with that catalog or return to the main menu
                NewCatalog(tree);
                break;
            case 2 :    //Takes user to state where they can perform different operations on an existing catalog
                UseCatalogMenu(tree, EditCatalog());
                break;
            case 3 :    //prints closing message and shuts down program
            default:    //put in default to termination just to be safe
                printf("\nProgram closing.\nThank you for using the IMDb Movie Catalog!\nGoodbye.\n\n");
                return 0;

        }

    }


}
