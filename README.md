# CS201imdb

## Brief Description: 
This program allows the user to create, read, update, and delete movies from the IMDb database in a personal catalog that will be saved beyond program termination.

## Overview of Program Operation:
**Overview describes successful scenarios**
After the user has started program execution the following output will appear:

    Welcome to the IMDb Movie Catalog!
    
    Initializing database. Please wait.
At this point the database is being loaded into a AVL tree.
If the user has correctly added title.basics.tsv to the folder then the main menu will appear:


    Would you like to:
    (1) Create a new catalog
    (2) Edit an existing catalog
    (3) Close program
    
Option 1 takes the user through the process of creating a new catalog. 
First the user has to specify the name of the catalog. This name must be unique (not the exact name of a preexisting catalog), starts with an english letter, and has the extension of ".txt". Once the user has picked a picked a name for their new catalog, he or she is then forced to add a movie to the catalog. A the end of this process the user can choose to continue editing the same catalog or return to main menu.


Option 2 allows the user to perform several different functions on an existing catalog.
First the user has to specify the name of an existing catalog that he or she would like to start working with again. Once the user has entered a valid catalog file name, the following movie menu will appear:

    Select what you would like to do with catalog CATALOGNAME:
    (1) Add a movie
    (2) Remove a movie
    (3) Update a movie's media type
    (4) Update a movie's date of acquisition
    (5) View a movie
    (6) View all titles
    (7) Return to main menu
    Enter number of choice:

Option 2.1 allows the user to create a new movie entry into the catalog.
The user is prompted to enter a partial or full movie title (IMPORTANT NOTE: If a movie that is being searched for starts with "A", "The", or "And" exclude it from the search for best intial search list results). The program will then search the entire IMDb movie database to find all movie's with titles that **start** with the entered string. Then a list of all matching titles is printed. The user is then prompted to enter the full title of the movie from the above list. This is a two step process to be as effective and simple as possible for the user. Once the user has entered the full movie title, the program then prompts the user to choose one of three movie types in which they own the movie with the following media menu:

    Choose the media type of the movie
    (1) dvd
    (2) bluray
    (3) digital
    Enter number of choice:
Then the user is prompted to enter the date that the movie was acquired. Date should be entered in the form of MM/DD/YYYY. Finally, the user is brought back to the movie menu with the just added movie as a part of the catalog in use. 

Option 2.2 allows the user to delete an existing movie from the catalog.
First the user is prompted to enter the full exact movie title. Once the title is entered, the program removes it from the catalog in use and returns the user to the movie menu.

Option 2.3 allows the user to update the media type of an existing movie in the catalog.
First the user is prompted to enter the full exact movie title. Then the user is prompted to pick a media type from the media menu. The movie is then updated to contain the newly selected media type. Finally, the user is brought back to the movie menu.

Option 2.4 allows the user to update the date of acquisition for an existing movie in the catalog.
First the user is prompted to enter the full exact movie title. Then the user is prompted to enter the new date in the form of MM/DD/YYYY. The movie is then updated to contain the newly entered date of acquisition. Finally, the user is brought back to the movie menu.

Option 2.5 allows the user to print all stored information for an existing movie in the catalog.
First the user is prompted to enter the full exact movie title. The information for that movie is then displayed in the following format: 

        Movie: XXXXX
        Genre(s): XXXXX
        Release Year: XXXXX
        Runtime: XXXXX minutes
        Media Type: XXXXX
        Date Acquired: XXXXX
It is possible that "\N"  can be displayed in the genre, realse year and/or runtime fields in place of the XXXXX if IMDb did not have that specific information for that movie. Finally, the user is brought back to the movie menu.

**Helpful tip: If the user is unsure of the exact movie title ("A" , "The", or "And" included at the start if applicable), then he or she can first use the following Option 2.6 before using Options 2.2 - 2.5**

Option 2.6 prints all stored information for every movie in the catalog.
When this option is selected the program prints the same format of information as Option 2.5 for every movie in the current catalog. Then the user is brought back to the movie menu.

Option 2.7 brings the user back to the state of the main menu.
This starts the process of saving the catalog to be used again even beyond program termination. A file is open under the same name as the catalog to write all of the information to. If there are no movies in the catalog, a 0 is written to the file. However, if it has at least 1 movie in the catalog, then a 1 is written on the first line and then all of the movie's information is written to the rest of the file. The movie information is seperated by tabs, and each movie is on its own line. After writing the new catalog file, it is closed, and the user is brought back to the main menu.

Option 3 terminates program execution.
The following is printed to the screen:

       Program closing.
       Thank you for using the IMDb Movie Catalog!
       Goodbye.
The program stops operation. The user is then brought back to regular terminal mode.


## Assumptions Made:



## Usage:
To use this program, download the code as a zip file from github
After unzipping the file, add title.basics.tsv to that folder
title.basics.tsv can be found at ADD THE LINK
This program is intended to work on Ubuntu 18.04 LTS (Bionic Beaver)
There is a makefile included in the project folder, so while in the project folder in the TERMINAL??? type

        make
The project will then have been compiled into an executable called "imdb", so to start the program type

        ./imdb

Program execution will only stop in 3 scenarios
1 - the user chooses Option 3 from the main menu,
2 - the program is stopped from the outside (closing window, shutting off the computer, CORRECT FOR LINUX??cntrl+c, etc...), or
3 - the user enters input greater than or equal to (250) characters.
***Program will exit without saving if you enter (250) or more characters at any input prompt, so dont do it because it is not necessary. 




## Choices Made:
1. Using an AVL tree as my main data structure
2. The user cannot see used catalog names in the program when creating a new catalog or trying to open an existing one.


## Reasoning for Choices:
1. After a few days of research, I concluded that an AVL Tree was the best data structure for me to use on this project. There were several motivating factors driving that choice. Firstly, an AVL Tree performs insertions, deletions, and searches in O(lg n) time. Also I have studied and coded binary search trees and red-black trees, so I am quite comfortable with the concept of BSTs. However, I had no previous experience with AVL trees in particular. this project served as a good opprtunity to learn and implement how they function. It is also a better form of a self-balancing BST than a red-black tree because it is stricter in its balancing. An AVL tree ensures that from any given node its left and right subtrees will only have a height differntial of 1. Both the database and individual catalogs utilize the same AVL tree functions.

2. Originally, I had allowed the user to view names of existing catalogs, but I decided it would be best to remove that functionality. The biggest reason for that choice is that it affected program storage and and running time negatively. view through task manager and command line, create extra data structure, now is O(1) time.
