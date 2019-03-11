#include "libraries.h"
#include "display.h"
#include "newCatalog.h"
#include "catalogs.h"


int main(void)
{
    StartUp();

    while(1)
    {

        int choice = MainMenu();
        switch (choice)
        {
            case 1 :
                NewCatalog();
                break;
            case 2 :
                EditCatalog();
                break;
            case 3 :
                return 0;
        }

    }


}
