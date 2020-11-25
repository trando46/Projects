//Bao Tran Do
//lab1.cpp
//September 19, 2020
//Purpose: This program place members into a 1D array and the ratings from
//         the members into a 2D array.
//Input: ask the uer to enter the file path for the rating.txt
//Process: Takes the user input
//Output: Display the members' and ratings' array contents.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Main application
int main() {

    //Declare variables
    ifstream infile;
    string fileName, line, rateLine;
    int numberOfBooks;
    //initialize the variables
    int numberOfMembers = 0;
    int counter = 0; //Keep track of the member and the ratings lines
    int row = 0; //keep track of row for ratings lines
    const int CAPACITY = 100; //assuming the resize of the arrays not necessary

    //create a dynamic 1D array of strings
    string *member = new string[CAPACITY];

    //Create a dynamic 2d array of integers
    int **ratings = new int*[CAPACITY];
    //creating the rows
    for (int i = 0; i < CAPACITY; i++)
        ratings[i] = new int[CAPACITY];

    //Ask the user to enter the rating file
    cout << "Enter the filepath: ";
    cin >> fileName;

    //Open the the file
    infile.open(fileName);

    //Read the file
    if(infile){
        //getting members into the array
        while (getline(infile, line) ) {
            //Put the ratings into the ratings array
            if(counter % 2 == 1){
                stringstream rate(line);
                numberOfBooks = 0;
                int readNumber = 0;
                while(rate >> readNumber) {
                    ratings[row][numberOfBooks] = readNumber;
                    numberOfBooks++;
                }
                row++;
            } else {
                //placing the members name into the member array
                member[numberOfMembers] = line;
                numberOfMembers++;
            }
            counter++;
        }
    } else {
        cout << "Error opening file ...\n";
    }

    //close the file
    infile.close();

    //Display the values from the arrays of members and ratings
    cout << endl;
    cout << "# of members: " << numberOfMembers << endl;
    cout << "# of books: " << numberOfBooks << endl << endl;
    for(int i = 0; i < numberOfMembers; i++){
        cout << "Name: "<< member[i] << endl;
        cout << "Ratings: ";
        for(int j =0; j < numberOfBooks; j++) {
            cout << ratings[i][j] << " ";
        }
        cout << endl << endl;
    }

    //deallocate memory for "members" & "ratings"
    for(int i = 0; i < CAPACITY; i++) {
        delete[] ratings[i];
    }
    delete[] member;
    delete[] ratings;

    return 0;
}
