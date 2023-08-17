//Bao Tran Do
//Lab2.cpp
//September 22, 2020
//Purpose: The purpose for this program is to read in the books.txt file to
//          populate the author, title, and year in an array and assign an
//          ISBN number to each book. The array should be able to resize when
//          the array runs out of space.
//Input: Ask the user to enter the file path for the books.txt
//Process: Takes the user input and populate that into an array
//Output: Display ths ISBN, Author, Title of the Book, and Year of the book.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BookList.h"
using namespace std;

//Main Application method
int main() {
    //Declare variables
    ifstream infile;
    string fileName,word,authorName,titleBook,yearBook;
    int counterWord;

    //Instantiate the BookList class
    const int SIZE = 40;
    BookList list(SIZE);

    //Ask the user to enter the rating file
    cout << "Enter the filepath: ";
    cin >> fileName;

    //Open the the file
    infile.open(fileName);

    //Read the file
    if (infile) {
        while (getline(infile, word)) {
            stringstream books(word);
            counterWord = 0;
            while (getline(books, word, ',')) {
                if(counterWord == 0){
                    //Get the author name
                    authorName = word;
                    counterWord++;
                } else if(counterWord == 1){
                    //Get the book title
                    titleBook = word;
                    counterWord++;
                } else {
                    //Get the year of the book
                    yearBook = word;
                    counterWord = 0;
                }
            }
            list.addBook(authorName,titleBook,yearBook);
        }

        //close the file
        infile.close();

        cout << endl;
        cout << "Total of books: " << list.size() << endl << endl;
        cout << list.to_string() << endl;

        return 0;
    }
}