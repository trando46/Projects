// Bao Tran Do
// File: lab3.cpp
// October 5, 2020
// Purpose: The purpose for this is to allow the user to enter any types of
//          input, and informs the user if the input was a palindrome.
// INPUT: Ask the user to enter the file path.
// PROCESS: Takes the user input and filter the user input into lower case
//          letters so that the program isn't case-sensitive and then ignore
//          any white spaces the user might enter. Traverse the string moving
//          forward and at the sametime backward to see if any conditions are
//          met. If the conditions are met return that condition (true or false)

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <functional>
#include <algorithm>
using namespace std;



bool isPalindrome(string);
// This function returns whether or not the string is a palindrome. The input
// string will be made as non case-sensitive and any white spacers will be
// ignored.
// IN: a string of the word that is read from the file
// MODIFY: none
// OUPUT: return true or false for a palindrome string
bool recursiveString(string, int, int);
// This function is the recursive function checking the string indexes. This
// function takes in a string and will traverse the string moving forward and
// backward until a certain condition is met by using first and last variables.
// IN: a string of a word that is read from the file
// MODIFY: none
// OUTPUT: if there is 1 letter in a string return true. If the last and first
//         characters do not match up return false. When both
//         of these conditions are not met traversing the string moving forward
//         and at the sametime moving backward have a base condition to return
//         true.

//Main application method
int main() {

    string word, fileName;
    ifstream infile;

    //Wecloming message
    cout << "Welcome to the palindrome testing program! " << endl;

    cout << "Enter the path: ";
    cin >> fileName;
    cout << endl;

    infile.open(fileName);

    if(infile){
        while(getline(infile,word)){
            if(isPalindrome(word)){
                cout << word << " is a palindrome!" << endl;
            } else {
                cout << word << " is NOT a palindrome." << endl;
            }
        }
    } else {
        cout << "Error opening file ...\n";
    }

    //close the file
    infile.close();

    cout << endl;
    //Display goodbye message
    cout << "Thanks for using the palindrome tester!" << endl;

    return 0;
}

bool isPalindrome(string text) {

    //have all the cases to be lower so the program isn't case-sensitive
    transform(text.begin(), text.end(), text.begin(), ::tolower);

    //ignore any white spaces
    text.erase(remove_if(text.begin(),text.end(), bind(isspace<char>,
            placeholders::_1, locale::classic())), text.end());

    return recursiveString(text,0,text.length() - 1);
}

bool recursiveString(string text, int firstEnd, int lastEnd){

    //Delcare and instantiate the variable
    int length = text.length();

    //If there is only one character
    if(length == 1){
        return true;
    }

    //Check if first(increment in the index) and last(decrement in the index)
    //do not match
    if(text[firstEnd] != text[lastEnd]) {
        return false;
    }

    //check if whether the first (moving up the string) is greater than or equal
    //the last (moving down the string). both first and last meet in the middle
    //without failing the other two conditions above ^ then it is a palindrome
    if(firstEnd >= lastEnd){
        return true;
    }

    //increment first so that it moves forward; decrement last so that it
    // moves backward so eventually first and last will meet in the middle
    return recursiveString(text, firstEnd + 1, lastEnd -1);
}






