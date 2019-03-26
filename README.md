# CS201imdb

Breif Description: 
This program allows the user to create, read, update, and delete movies from the IMDb database in a personal catalog that will be saved beyond program termination.

Overview of Program Operation:
After the user has started program execution the following output will appear:
    Welcome to the IMDb Movie Catalog!

    Initializing database. Please wait.
At this point the database is being loaded into a AVL tree.
If you have correctly added title.basics.tsv to the folder then the main menu will appear:
    Would you like to:
    (1) Create a new catalog
    (2) Edit an existing catalog
    (3) Close program
Option 1 takes the user through the process of creating a new catalog. 
First the user has to specify the name of the catalog. This name must be unique (not the exact name of a preexisting catalog). Once the user has picked a picked a name for their new catalog, he or she is then forced to add a movie to the catalog. A the end of this process the user can choose to continue editing the same catalog or return to main menu.




Choices Made:
1. Using an AVL tree as my main data structure
2. The user cannot see used catalog names in the program when creating a new catalog or trying to open an existing one.


Reasoning for Choices:
1. After a few days of research, I concluded that an AVL Tree was the best data structure for me to use on this project. There were several motivating factors driving that choice. Firstly, an AVL Tree performs insertions, deletions, and searches in O(lg n) time. Also I have studied and coded binary search trees and red-black trees, so I am quite comfortable with the concept of BSTs. However, I had no previous experience with AVL trees in particular. this project served as a good opprtunity to learn and implement how they function. It is also a better form of a self-balancing BST than a red-black tree because it is stricter in its balancing. An AVL tree ensures that from any given node its left and right subtrees will only have a height differntial of 1. 

2. Originally, I had allowed the user to view names of existing catalogs, but I decided it would be best to remove that functionality. The biggest reason for that choice is that it affected program storage and and running time negatively. view through task manager and command line, create extra data structure, now is O(1) time.
