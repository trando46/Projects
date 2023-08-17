// Bao Tran Do
// File: lab4.cpp
// October 12, 2020
// Purpose: The purpose for this is to reused the same code from the LinkList
//          class but for different data types and to display the last negative
//          value entered.
// INPUT: none
// OUTPUT: Display the LinkedList contents and the last negative number 

#include <iostream>
#include "LinkedList.h"
using namespace std;

void callingDouble();
// This function instantiate the LinkList class for data type that is double.
// Append any value double value to the LinkedList, print out the content of the
// content of the list and display the last negative value entered
// IN: none
// MODIFY: none
// OUTPUT: none
void callingInt();
// This function instantiate the LinkList class for data type that is double.
// Append any value double value to the LinkedList, print out the content of the
// content of the list and display the last negative value entered
// IN: none
// MODIFY: none
// OUTPUT: none

// Main application method
int main() {

    //Calling the functions for int and doubles
    callingInt();
    cout << "-------------------------------------------------" << endl;
    callingDouble();

    return 0;
}

void callingDouble(){
    //Creating a linked list that takes the doubles
    LinkedList<double> listDouble;
    cout << "DOUBLES" << endl;
    cout << "Adding -3.2, 2.14, -5.7, -12.01, -2.99, 4.6, 5.2..." << endl;
    listDouble.appendNode(-3.2);
    listDouble.appendNode(2.14);
    listDouble.appendNode(-5.7);
    listDouble.appendNode(-12.01);
    listDouble.appendNode(-2.99);
    listDouble.appendNode(4.6);
    listDouble.appendNode(5.2);

    // print list
    cout << "Linked list contents: " << listDouble.to_string();
    cout << "Last negative number: " << listDouble.getLastNegative() << endl;
}

void callingInt(){
    //Creating a linked list that takes the integers
    LinkedList<int> listInt;

    cout << "INTEGERS" << endl;
    cout << "Adding 3, -2, 5, 12, -2, -4, 5...\n";
    listInt.appendNode(3);
    listInt.appendNode(-2);
    listInt.appendNode(5);
    listInt.appendNode(12);
    listInt.appendNode(-2);
    listInt.appendNode(-4);
    listInt.appendNode(5);

    // print list
    cout << "Linked list contents: " << listInt.to_string();
    cout << "Last negative number: " << listInt.getLastNegative() << endl;
}