# Personal Movie Database

## Brief Description: 
This program allows the user to create, read, update, and delete movies from the IMDb database in a personal catalog that will be saved beyond program termination.

## Overview of Program Operation:

Walkthrough video can be found at https://www.youtube.com/watch?v=7x1oVnYvGqM

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
First the user has to specify the name of the catalog. This name must be unique (not the exact name of a preexisting catalog), starts with an english letter, at most 100 characters long, conatains 1 '.' and 0 spaces, and has the extension of ".txt". Once the user has picked a picked a name for their new catalog, he or she is then forced to add a movie to the catalog. A the end of this process the user can choose to continue editing the same catalog or return to main menu.


Option 2 allows the user to perform several different functions on an existing catalog.
First the user has to specify the name of an existing catalog (including the .txt extension) that he or she would like to start working with again. Once the user has entered a valid catalog file name, the following movie menu will appear:

    Select what you would like to do with catalog CATALOGNAME:
    (1) Add a movie
    (2) Remove a movie
    (3) Update a movie's media type
    (4) Update a movie's date of acquisition
    (5) View a movie
    (6) View all info for all movies in the catalog
    (7) Save catalog and return to main menu
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
First the user is prompted to enter the full exact movie title. Once the title is entered, the program removes it from the catalog in use. If no error message is printed then it was successfully removed. The user then returns the user to the movie menu.

Option 2.3 allows the user to update the media type of an existing movie in the catalog.
First the user is prompted to enter the full exact movie title. Then the user is prompted to pick a media type from the media menu. The movie is then updated to contain the newly selected media type. If no error message is printed then the update was successful. Finally, the user is brought back to the movie menu.

Option 2.4 allows the user to update the date of acquisition for an existing movie in the catalog.
First the user is prompted to enter the full exact movie title. Then the user is prompted to enter the new date in the form of MM/DD/YYYY. The movie is then updated to contain the newly entered date of acquisition. If no error message is printed then the update was successful.  Finally, the user is brought back to the movie menu.

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


## Usage:
Follow the steps below to get the program up and running.
Download the code as a zip file from github
Unzip the file to an empty folder.
Go to https://datasets.imdbws.com/
Download the file title.basics.tsv.gz
Unzip the file and add title.basics.tsv to the folder that the code is in
It is possible that the tsv file could've been downloaded under the name data.tsv or another name. If so, change the name to title.basics.tsv
This program is intended to work on Ubuntu 18.04 LTS (Bionic Beaver)
There is a makefile included in the project folder, so while in the project folder in the terminal type

        make
The project will then have been compiled into an executable called "imdb", so to start the program type

        ./imdb


Program execution will only stop in 3 scenarios:
1 - the user chooses Option 3 from the main menu,
2 - the program is stopped from the outside (closing window, shutting off the computer, ctrl+c, etc...), or
3 - the user enters input greater than or equal to 250 characters.
***Program will exit without saving if you enter 250 or more characters at any input prompt, so dont do it because it is not necessary.

Important notes:
-The file exit.txt is included in the project folder so that if a user tries to edit an existing catalog without ever having created a catalog then he or she can type

        exit.txt
and then choose option 7 in the movie menu to return to the main menu and create a new catalog.
***never remove exit.txt from the project folder

-When doing the intial search for a movie to add, exclude "The", "And", or "A" if that is what the first word of the title is unless you are typing the full exact title. Movies that have at least the first two words being a combination from the three articles can only be found in a search wih the Full exact movie title.
-If the user enters a valid full exact movie title of a movie not in the printed list from the inital search, that movie will still be added to the catalog.
-When entering date of acquisition for a movie the form MM/DD/YYYY is specified, but anything that is 10 characters long is actually acceptable. Just by saying MM/DD/YYYY it makes it clear form the form of the date, but if the user wants to put some random 10 character string, I am okay with that because it is their catalog and they can update it to a real date later if they choose to do so.
-When 250 or more characters are entered at input, the program may or may not save the working catalog depending on the current state. Also when this error occurs and the program exits, the input will most likely be tried as terminal commands.


## Choices Made:
1. Using an AVL tree as my main data structure
2. The user cannot see used catalog names in the program when creating a new catalog or trying to open an existing one.


## Reasoning for Choices:
1. After a few days of research, I concluded that an AVL Tree was the best data structure for me to use on this project. There were several motivating factors driving that choice. Firstly, an AVL Tree performs insertions, deletions, and searches in O(lg n) time. Also I have studied and coded binary search trees and red-black trees, so I am quite comfortable with the concept of BSTs. However, I had no previous experience with AVL trees in particular. this project served as a good opprtunity to learn and implement how they function. It is also a better form of a self-balancing BST than a red-black tree because it is stricter in its balancing. An AVL tree ensures that from any given node its left and right subtrees will only have a height differntial of 1. Both the database and individual catalogs utilize the same AVL tree functions.

2. Originally, I had allowed the user to view names of existing catalogs, but I decided it would be best to remove that functionality. The biggest reason for that choice is that it affected program storage and running time negatively. Text file names can viewed in the project folder. This method avoids creating an uneseccasry data structure. The operation now performs in O(1) time.



Citations:
1. All noted functions in the code were modified from Neeraj Mishra's "Program for AVL Tree in C"
    https://www.thecrazyprogrammer.com/2014/03/c-program-for-avl-tree-implementation.html
