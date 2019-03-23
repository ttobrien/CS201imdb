#include "libraries.h"
#include "display.h"
#include "newCatalog.h"
#include "catalogs.h"
#include "avlTree.h"


int main(void)
{
    Movie *tree = StartUp();

    while(1)
    {

        int choice = MainMenu();
        switch (choice)
        {
            case 1 :
                NewCatalog(tree);
                break;
            case 2 :
                UseCatalogMenu(tree, EditCatalog());
                break;
            case 3 :
                return 0;
        }

    }


}
