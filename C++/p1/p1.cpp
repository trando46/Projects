// Bao Tran Do
// File: p1.cpp
// September 28, 2020
// Purpose: The purpose for this is to allow the user to add new books, give
//         ratings to the books, and see the recommendation of books that they
//         share their similarities with.
// Input: Ask the user to enter the file path for books.txt and ratings.txt.
//         Allow the user to add new members, books characteristics, ratings,
//         and access any features of the menu inputs.
// Process: Takes the user input and populate them in 1D and 2D dynamic arrays.
//         1D arrays consists of members and books characteristics.
//         2D arrays consists of ratings of books from the members. User can
//         access their information when they are login into their account.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"
using namespace std;

void populateAllClasses(string,string,MemberList &,BookList &,RatingList &);
// This function populates all the information into its appropriate classes and
// calls the main menu function
// IN: a string for the file path books.txt and a string for ratings.txt.
//          getting addresses of the MemberList, BookList, and RatingList's
//          class arrays
// MODIFY: none
// OUTPUT: none
void mainMenu(MemberList &,BookList &,RatingList &);
// This function create the main menu the user will see when using this program
// IN: getting addresses of the MemberList, BookList, and RatingList's
//           class arrays
// MODIFY: none
// OUTPUT: none
void loginMenu(MemberList &, BookList &,RatingList &,int);
// This function display the menu when the user login into their account
// IN: getting addresses of the MemberList, BookList, and RatingList's class
//           arrays and an integer number for the user account number.
// MODIFY: none
// OUTPUT: none
void addMember(MemberList &);
// This function add new members to the program
// IN: getting address of the MemberList's class array
// MODIFY: none
// OUTPUT: none
void addBook(BookList &);
// This function add new books to the program
// IN: getting address of the BookList's class array
// MODIFY: none
// OUTPUT: none
void rateBook(BookList &, MemberList &, RatingList &, int);
// This function allows the user to rate a book
// IN: getting addresses of the MemberList, BookList, and RatingList's class
//           arrays and an integer number for the user account number.
// MODIFY: none
// OUTPUT: none
void viewRatings(BookList &, MemberList &,RatingList &, int);
// This function allows the user to view their own ratings of books
// IN: getting addresses of the MemberList, BookList, and RatingList's class
//           arrays and an integer number for the user account number.
// MODIFY: none
// OUTPUT: none
void seeRecommendations(BookList &, MemberList &, RatingList &, int);
// This function allows the user to see some of the recommendation of books
// base on which members from this program share the most similarities to them
// IN: getting addresses of the MemberList, BookList, and RatingList's class
//           arrays and an integer number for the user account number.
// MODIFY: none
// OUTPUT: none

//Main Application method
int main() {

    //Declare variables
    ifstream infileRating;
    string fileNameRating, fileNameBook;

    //Size of the array
    const int SIZE = 40;

    //Instantiate the classes
    MemberList memberList(SIZE);
    BookList bookList(SIZE);
    RatingList ratingList(SIZE);

    //Display the welcoming message
    cout << "Welcome to the Book Recommendations Program! \n"
        << "This program is designed for you to keep track of the books that \n"
        << "you may or may not have read and along with the ratings you give \n"
        << "to the books. You are more than welcome to add new members and \n"
        << "add new books. The new books will be added to the list of books \n"
        << "so that other members can view them too. You can also see the \n"
        << "the recommendations of new books that you haven't read yet from \n"
        << "the member from this program that have the most similarities to \n"
        << "you. Have fun reading! " << endl << endl << endl;



    //Ask the user to enter the rating file
    cout << "Enter the  books filepath: ";
    cin >> fileNameBook;

    //Ask the user to enter the rating file
    cout << "Enter the  rating filepath: ";
    cin >> fileNameRating;
    populateAllClasses(fileNameRating,fileNameBook,memberList,
                       bookList,ratingList);

    return 0;
}

void populateAllClasses(string fileNameRating, string fileNameBook,
                        MemberList &memberList, BookList &bookList,
                        RatingList &ratingList){

    //Declare the variables and instantiate them
    string wordB, word, authorName, titleBook, yearBook;
    int counterWord = 0,row = 0,counter,numberOfBooks = 0,numberOfMembers = 0;
    ifstream infileRating,infileBooks;

    //Open the the file
    infileBooks.open(fileNameBook);

    //Read the file
    if (infileBooks) {
        ///Books.txt
        while (getline(infileBooks, wordB)) {
            stringstream books(wordB);
            counter = 0;
            while (getline(books, wordB, ',')) {
                if (counter == 0) {
                    //Get the author name
                    authorName = wordB;
                    counter++;
                } else if (counter == 1) {
                    //Get the book title
                    titleBook = wordB;
                    counter++;
                } else {
                    //Get the year of the book
                    yearBook = wordB;
                    counter = 0;
                }
            }
            bookList.addBook(authorName, titleBook, yearBook);
        }
    } else {
        cout << "Error opening file ...\n";
    }

    //close the file
    infileBooks.close();

    //Open the the file
    infileRating.open(fileNameRating);

    //Read the file
    if (infileRating) {
        while (getline(infileRating, word) ) {
            if (counterWord % 2 == 1) {
                stringstream rate(word);
                numberOfBooks = 0;
                int readNumber = 0;
                while (rate >> readNumber) {
                    ratingList.addRating(row, numberOfBooks, readNumber);
                    numberOfBooks++;
                }
                row++;
            } else {
                memberList.addMember(word);
                numberOfMembers++;
            }
            counterWord++;
        }
    } else {
        cout << "Error opening file ...\n";
    }

    //close the file
    infileRating.close();

    //Display the number of books and number of members from file
    cout << endl;
    cout << "Number of books: " << numberOfBooks << endl;
    cout << "Number of members: " << numberOfMembers << endl << endl;

    //Call for the main menu
    mainMenu(memberList,bookList,ratingList);
}

void mainMenu(MemberList &memberList, BookList &bookList, RatingList &ratingList) {

    //Declare the variables
    int option, accountNumber;
    string name,titleOfBook,year;

    do {
        //Display the menu
        cout << "************** MENU **************" << endl;
        cout << "* 1. Add a new member            *" << endl;
        cout << "* 2. Add a new book              *" << endl;
        cout << "* 3. Login                       *" << endl;
        cout << "* 4. Quit                        *" << endl;
        cout << "**********************************" << endl << endl;

        //Ask the user to enter their option
        cout << "Enter a menu option: ";
        cin >> option;
        cout << endl;

        switch(option){
            case 1:
                addMember(memberList);
                break;
            case 2:
                addBook(bookList);
                break;
            case 3:
                //Ask the user to enter their account number
                cout << "Enter member account: ";
                cin >> accountNumber;
                cout << memberList.get(accountNumber) << ", you are logged in!";
                cout << endl << endl;
                loginMenu(memberList,bookList,
                         ratingList, accountNumber);
                break;
            case 4:
                cout << endl;
                break;
        }
    } while(option != 4 && option >= 1);
    if(option == 4 ){
        cout << "See you later!" << endl;
        exit(0);
    }
}

void loginMenu(MemberList &memberList, BookList &bookList,
               RatingList &ratingList, int accountNumber){

    //Declare variables
    int option;
    string name,titleOfBook,year;

    do {
        //Display the menu
        cout << "************** MENU **************" << endl;
        cout << "* 1. Add a new member            *" << endl;
        cout << "* 2. Add a new book              *" << endl;
        cout << "* 3. Rate book                   *" << endl;
        cout << "* 4. View ratings                *" << endl;
        cout << "* 5. See recommendations         *" << endl;
        cout << "* 6. Logout                      *" << endl;
        cout << "**********************************" << endl << endl;

        //Ask the user to enter their option
        cout << "Enter a menu option: ";
        cin >> option;
        cout << endl;

        switch (option) {
            case 1:
                addMember(memberList);
                break;
            case 2:
                addBook(bookList);
                break;
            case 3:
                rateBook(bookList, memberList,
                        ratingList, accountNumber);
                break;
            case 4:
                viewRatings(bookList, memberList,
                           ratingList,accountNumber);
                break;
            case 5:
                seeRecommendations(bookList,memberList,
                                 ratingList,accountNumber);
                break;
            case 6:
                cout << "You are logged out!" << endl << endl;
                mainMenu(memberList, bookList, ratingList);
                break;
        }
    } while (option <=6 && option >= 1);
}

void addMember(MemberList &memberList){
    //Declare variables
    string name;

    cout << "Enter your name: ";
    cin >> name;
    memberList.addMember(name);
    cout << name << " (account #: " << memberList.sizeMember() << ") was added"
         << endl << endl;
}

void addBook(BookList &bookList){
    //Declare variables
    string author, title,year;

    cout << "Enter the author: ";
    cin >> author;
    cout << "Enter the title of the book: ";
    cin >> title;
    cout << "Enter the year of the book: ";
    cin >> year;

    //Add the book information
    bookList.addBook(author,title,year);

    cout << "You added " << author << ", " << title << ", " << year << endl;
}

void rateBook(BookList &bookList, MemberList &memberList,
              RatingList &ratingList, int accountNumber){
    //Declare variables
    int ISBN, rating;
    string rerate;

    cout << "Enter the ISBN for the book you'd like to rate: ";
    cin >> ISBN;

    // Check if the member rating is 0 and if it is ask them to enter a rating
    if(ratingList.getMemberRating(accountNumber-1,ISBN-1) == 0 ){
        cout << "Rating status: Hated it! => -5  Didn't like it => -3\nHaven't"
                "read it => 0  Ok - neither hot nor cold about it => 1\n"
                "Liked it => 3  Really liked it! => 5"  << endl;
        cout << "Enter your rating: ";
        cin >> rating;

        //Add the rating to the book for that member
        //ratingList.addRating(accountNumber-1,ISBN-1,rating);
        ratingList.addMemberRating(accountNumber,ISBN,rating);

        cout << "Your new rating for ISBN: " << bookList.getBook(ISBN)
             << " => rating: " <<
             ratingList.getMemberRating(accountNumber-1,ISBN-1) << endl;
    } else {
        cout << "Your current rating for " << bookList.getBook(ISBN)
             << " => rating: "
             << ratingList.getMemberRating(accountNumber-1,ISBN-1) << endl;
        cout << "Would you like to re-rate this book (y/n)?";
        cin >> rerate;
        if(rerate == "y"){
            cout << "Enter your new rating: ";
            cin >> rating;

            //Add the rating to the book for that member
            ratingList.addMemberRating(accountNumber,ISBN,rating);

            cout << "Your new rating for ISBN: " << bookList.getBook(ISBN)
                 << " => rating: " <<
                 ratingList.getMemberRating(accountNumber-1,ISBN-1) << endl;
        }
    }
}

void viewRatings(BookList &bookList, MemberList &memberList,
                 RatingList &ratingList, int accountNumber){

    //Display the members' ratings
    cout << memberList.get(accountNumber) << "'s ratings ..." << endl;

    for(int i = 0; i < bookList.sizeBook(); i++){
        cout << bookList.getMemberBooks(i) << " => rating: " <<
        ratingList.getMemberRating(accountNumber-1,i) << endl;
    }
    cout << endl;
}

void seeRecommendations(BookList &bookList, MemberList &memberList,
                       RatingList &ratingList, int accountNumber){

    //Declare and instantiate variables
    int maxValue = INT16_MIN, matchingToUser, idMatcher;

    for(int row = 0; row < memberList.sizeMember(); row ++){
        matchingToUser = 0;
        for(int col = 0; col < bookList.sizeBook(); col++){
            if( row != accountNumber){
                matchingToUser += ratingList.getMemberRating(accountNumber,col)
                        * ratingList.getMemberRating(row,col);
            }
        }
        //check to see which user have the highest score for similarities
        if(matchingToUser > maxValue) {
            maxValue = matchingToUser;
            idMatcher = row+1;
        }
    }

    //Display who they share similar taste with
    cout << "You have similar taste in books as " << memberList.get(idMatcher)
        << "!" << endl << endl;

    //Get all the books that the matched user liked the most and the account
    // member that havent read it yet
    cout << "Here are the books they really liked with a rating of 5 \n"
        << "and you haven't read: "
        << endl;
    for(int i = 0; i < bookList.sizeBook(); i++) {
        if(ratingList.getMemberRating(idMatcher-1,i) == 5 &&
            ratingList.getMemberRating(accountNumber-1,i) == 0){
            cout << bookList.getMemberBooks(i) << endl;
        }
    }
    cout << endl;

    //Get all the books that the matched user liked and the account
    // member that havent read it yet
    cout << "And here are the books they liked with a rating of 3 \n"
        << "and you haven't read: " << endl;
    for(int i = 0; i < bookList.sizeBook(); i++){
        if(ratingList.getMemberRating(idMatcher-1,i) == 3 &&
            ratingList.getMemberRating(accountNumber-1,i) == 0){
            cout << bookList.getMemberBooks(i) << endl;
        }
    }
    cout << endl;

    //Get all the books that the matched user really dislikes
    cout << "And here are the books they really dislike with a rating of -5:\n";

    for(int i = 0; i < bookList.sizeBook(); i++){
        if(ratingList.getMemberRating(idMatcher-1,i) == -5){
            cout << bookList.getMemberBooks(i) << endl;
        }
    }
    cout << endl;
}

