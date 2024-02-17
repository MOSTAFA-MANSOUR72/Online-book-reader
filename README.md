# Online-book-reader
A Console Online ebooks reader to read and manage ebooks

# Features:
- System can serve the user to read and choose books to read on system
- System is managed by admins who add and delete books from system
  
![image](https://github.com/MOSTAFA-MANSOUR72/Online-book-reader/assets/149438807/a5d5d0b6-8983-44e3-a10d-edfea1dbbbc8)

## What can admin do
- View Profile
- Change Name
- Change UserName
- Change Password
- Add a New Book
- Delete A Book
- EXIT

## What User can do 
user has much more choices than admin ,as he the main user of the program :
-to view profile or edite it.
-to search for a book by name.
-to list the current system books.
-to list his own choosen books to read (books he is reading ).
-to choose a new book from the system to read and then he make a new seasion for reading it.
-to delete a seasion.

## how data is stored 
***file based system***
 as its a quite simple project with console , i used the iofsream library in c++ to use filebased system to store my data instead of using database
 the arrangement of data of every file is described inside the code in the ***loadData*** functions for every file or entity
 - data is loaded and uploaded in system by two functions exist in every manager class ( loadData() - UploadData() ) .
   
## Some Interfaces shoots

  - Main page

    ![image](https://github.com/MOSTAFA-MANSOUR72/Online-book-reader/assets/149438807/07601f3b-15f9-49ef-bf98-e15004b74a89)

- listing current books
  
![image](https://github.com/MOSTAFA-MANSOUR72/Online-book-reader/assets/149438807/2660473a-ea53-40ad-b938-3eef2690e5d3)

- view my seasions
  
![image](https://github.com/MOSTAFA-MANSOUR72/Online-book-reader/assets/149438807/39e0b06a-a344-4aac-abd2-c359945edc27)
  
- Opening a seasion and starting to read a book
  
![image](https://github.com/MOSTAFA-MANSOUR72/Online-book-reader/assets/149438807/8ea5b96b-c8ec-4fae-895e-fc5a8fe6e5f0)

# Data structures used & oop concepts
- some STL templates Like:
  - vector of string to store books pages
  - map of string and book class to get the book info by name or by id
  - map of string and boolean to add the deleted books or seasions to the black list
- tried to design my classes with abstractions to make it clear and easy to know classes functionalities
- usage of intities is managed by manager classes like sessionManager, UserManager and adminManager
- data are not static because of using files and iofstream to store it and retrieve it again when it is needed.
  
