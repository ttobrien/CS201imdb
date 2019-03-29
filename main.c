#include "libraries.h"
#include "display.h"
#include "newCatalog.h"
#include "catalogs.h"
#include "avlTree.h"


int main(void)//convince her of good choices, data structures, and testing. USE STRNCMP AND STRNCPY use char * to read in input and then strncpy and %200s, bigger title space, can crash if run out of heap
{             // before exit(1) try to save catalog?
              // read in single strings as whole input [^\n] and then extract the first part until space
              //free space of Movie after deleted
              //convert to key needs to be fixed
              //fclose on NULL
              //string ops on pointers
              //add not about not typing continuously (clicking or keying left)

    Movie *tree = StartUp(); //Does introductory output and creates and stores the avl Tree from the IMDb data file

    if(tree == NULL) //Program closes if datafile is not found since there is not much a user could do without the database
    {
        printf("\nDatabase not loaded. Exiting program.\n\n");
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
            case 3 :    //printd closing message and shuts down program
            default:    //put in default with termination just to be safe
                printf("\nProgram closing.\nThank you for using the IMDb Movie Catalog!\nGoodbye.\n\n");
                return 0;

        }

    }


}
