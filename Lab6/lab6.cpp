// Bao Tran Do
// File: lab6.cpp
// November 10, 2020
// Purpose: The purpose for this is to implement a HashTable using the hash
//          function h(k) = k % N and linear probing for the collision
// Input: none. (This is hardcoded)
// Process: none. (Process the hardcode. Generate 4083 unique numbers and then
//          add 10 additional key/value pairs


#include <iostream>
#include "HashTable.h"
#include <string>
using namespace std;

void containsString(HashTable & , int num);
// This function displays whether or not the HashTable contains the key
// IN: A reference to the HashTable and the key
// MODIFY: none
// OUTPUT: none
void welcome(HashTable & hashT, int & CAP);
// This function displays the welcome message
// IN: A reference to the HashTable and the capacity
// MODIFY: none
// OUTPUT: none
void goodBye();
// This function displays the goodbye message
// MODIFY: none
// OUTPUT: none

//Main application method
int main() {

    static int CAPCITY = 4093;
    static int UNIQUE = 4083;
    static int RANGE = 10000;

    //Instantiate the HashTable
    HashTable hash(CAPCITY);

    //Generate UNIQUE numbers
    int random;
    for(int i = 1; i <= UNIQUE; i++ ){
        random = (rand() % RANGE ) + 1;
        hash.put(i,random);
    }

    welcome(hash,CAPCITY);

    cout << "Inserting 10 additional key/value table size: " << endl;
    //Adding 10 additional key/value pairs into the table
    cout << "(1179 , 120)\n"
            "(9702 , 121)\n"
            "(7183 , 122)\n"
            "(50184 , 123)\n"
            "(4235 , 124)\n"
            "(644 , 125)\n"
            "(77 , 126)\n"
            "(3077 , 127)\n"
            "(23477 , 128)\n"
            "(90777 , 129)\n";
    hash.put(1179,120);
    hash.put(9702,121);
    hash.put(7183,122);
    hash.put(50184,123);
    hash.put(4235,124);
    hash.put(644,125);
    hash.put(77,126);
    hash.put(3077,127);
    hash.put(23477,128);
    hash.put(90777,129);


    //testing contains
    cout << endl;
    cout << "Testing contains..." << endl;
    containsString(hash,50184);
    containsString(hash,77);
    containsString(hash,0);
    containsString(hash,-1);
    containsString(hash,1179);
    containsString(hash,9702);
    containsString(hash,4235);
    containsString(hash,644);
    containsString(hash,3077);
    containsString(hash,23477);
    containsString(hash,90777);

    //Testing get
    cout << endl;
    cout << "Testing get..." << endl;
    cout << "get(50184):" << hash.get(50184) << endl;
    cout << "get(   77)::" << hash.get(77) << endl;
    cout << "get(    0):" << hash.get(0) << endl;
    cout << "get(   -1):" << hash.get(-1) << endl;
    cout << "get(   1179):" << hash.get(1179) << endl;
    cout << "get(   9702):" << hash.get(9702) << endl;
    cout << "get(   7183):" << hash.get(7183) << endl;
    cout << "get(   4235):" << hash.get(4235) << endl;
    cout << "get(    644):" << hash.get(644) << endl;
    cout << "get(   3077):" << hash.get(3077) << endl;
    cout << "get(  23477):" << hash.get(23477) << endl;
    cout << "get(  90777):" << hash.get(90777) << endl;

    cout << endl;
    cout << "After inserting 10 additional key/value, "
            "the number of elements present: " << hash.size() << endl << endl;

    goodBye();
    return 0;
}
void containsString(HashTable & hashT, int num){

    if(hashT.contains(num)){
        cout << "contains(  " << num << "): true" << endl;
    } else {
        cout << "contains(  " << num << "): false" << endl;
    }
}

void welcome(HashTable & hashT, int & CAP){
    cout << "Welcome to the HashTable testing program.\n\n" << "Creating a new"
            "HashTable with capacity " << CAP << " and inserting\n"
            << hashT.size() << " random key-value pairs with unique "
             "keys..done.\n\n";
}

void goodBye(){
    cout << "Thanks for using the HashTable testing program. Goodbye!\n";
}


