// Bao Tran Do
// File: p2.cpp
// October 19, 2020
// Purpose: The purpose for this is to allow the user to enter an integer and a
//          string file. The data from the two files will then be populated
//          into a binary search tree. The user can see the characteristics of
//          the tree.
// Input: Ask the user to enter the file path for the integers and the strings
// Process: Takes the user input and populate that into Nodes(root, left, and
//          right) to create the binary search tree.

#include <iostream>
#include <fstream>
#include "BST.h"

void intFile();
// This function populates all the information of integers from the file and
// displays all of the test cases: copy constructor, assignment operator,
// insert, level and ancestors, contains, remove, and repeat again for insert,
// level and ancestors, and remove.
// IN: a file that contains the integers -> integers.dat
// Modify: none
// OUTPUT: none
void strFile();
// This function populates all the information of strings from the file and
// displays all of the test cases: copy constructor, assignment operator,
// insert, level and ancestors, contains, remove, and repeat again for insert,
// level and ancestors, and remove.
// IN: a file that contains the strings -> strings.dat
// MODIFY: none
// OUTPUT: none
void TestInsert(int, int, int, bool);
// This function display the test case for testing inserting value. Display
// the number of nodes, number of leaves, BST height, and is BST empty.
// IN: the BST size, BST leaf count, BST height, and BST empty functions
// MODIFY: none
// OUTPUT: none
void TestTraversals(string, string, string);
// This function display the pre-order, in-order, and post-order of the BST.
// IN: the BST get pre-order, in-order, and post-order functions
// MODIFY: none
// OUTPUT: none
template <typename T>
void TestLevelAncestors(BST<T> &, T, int, string);
// This is a template function that display the level and ancestors for both
// BST of strings and integers.
// IN: A reference to the tree, the value for a particular type, BST level and
//          ancestors functions.
// MODIFY: none
// OUTPUT: none
template <typename T>
void testCopyConstructor(BST<T> &);
// This is a template function that display the copy constructor for both
// BST of strings and integers.
// IN: A reference to the tree
// MODIFY: none
// OUTPUT: none
template <typename T>
void testAssignmentOperator(BST<T> &);
// This is a template function that display the assignment operator for both
// BST of strings and integers.
// IN: A reference to the tree
// MODIFY: none
// OUTPUT: none
template <typename T>
void TestContains(BST<T> &, T, bool);
// This is a template function that display contains for both
// BST of strings and integers.
// IN: A reference to the tree, the value for a particular type, BST contain
//          function.
// MODIFY: none
// OUTPUT: none


int main() {

    cout << "Welcome to the Binary Search Tree program! This program allows \n"
            "you to insert an integer file and a string file. The file will \n"
            "be process and be display as a Binary Search Tree. The output \n"
            "will contain all of the characteristics of the "
            "Binary Search \nTree." << endl;
    cout << endl << endl;

    intFile();
    strFile();

    cout << endl;

    cout << "Thank you! Goodbye!" << endl;

    return 0;
}

void intFile(){
    //Declare the variables
    ifstream infile;
    string intFile, intWord;

    //Instantiate the int BST
    BST<int> intBST;

    cout << "******************************" << endl;
    cout << "* INTEGER BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl << endl;

    cout << "** CREATE BST **" << endl;
    TestInsert(0,0,0,intBST.empty());

    cout << endl;

    cout << "Enter integer file: ";
    cin >> intFile;
    cout << endl;

    infile.open(intFile);

    ///cout << "Inserting in this order: ";
    if(infile){
        while(getline(infile,intWord)){
            int number = stoi(intWord);
            ///cout << number << " ";
            intBST.insert(number);
        }
        cout << endl;
    } else {
        cout << "Error opening file ...\n";
    }

    infile.close();

    //Display the TEST INSERT
    cout << "** TEST INSERT **" << endl;
    cout << "Inserting in this order: 40 20 10 30 60 50 70 " << endl;
    TestInsert(intBST.size(),intBST.getLeafCount(),
               intBST.getHeight(),intBST.empty());
    cout << endl;

    //Display the TEST COPY CONSTRUCTOR
    testCopyConstructor(intBST);

    //Display the TEST ASSIGNMENT OPERATOR
    testAssignmentOperator(intBST);

    //Display the TEST TRAVERSALS
    cout << "** TEST TRAVERSALS **" << endl;
    TestTraversals(intBST.getPreOrderTraversal(),
                   intBST.getInOrderTraversal(),intBST.getPostOrderTraversal());
    cout << endl;

    //Display the TEST LEVEL & ANCESTORS
    cout << "** TEST LEVEL & ANCESTORS **" << endl;
    TestLevelAncestors(intBST,40,intBST.getLevel(40),
                       intBST.getAncestors(40));
    TestLevelAncestors(intBST,20,intBST.getLevel(20),
                       intBST.getAncestors(20));
    TestLevelAncestors(intBST,10,intBST.getLevel(10),
                       intBST.getAncestors(10));
    TestLevelAncestors(intBST,30,intBST.getLevel(30),
                       intBST.getAncestors(30));
    TestLevelAncestors(intBST,60,intBST.getLevel(60),
                       intBST.getAncestors(60));
    TestLevelAncestors(intBST,50,intBST.getLevel(50),
                       intBST.getAncestors(50));
    TestLevelAncestors(intBST,70,intBST.getLevel(70),
                       intBST.getAncestors(70));
    TestLevelAncestors(intBST,1,intBST.getLevel(1),
                       intBST.getAncestors(1));

    //Test contains
    cout << endl;
    cout << "** TEST CONTAINS **" << endl;
    TestContains(intBST,20,intBST.contains(20));
    TestContains(intBST,40,intBST.contains(40));
    TestContains(intBST,10,intBST.contains(10));
    TestContains(intBST,70,intBST.contains(70));
    TestContains(intBST,99,intBST.contains(99));
    TestContains(intBST,-2,intBST.contains(-2));
    TestContains(intBST,59,intBST.contains(59));
    TestContains(intBST,43,intBST.contains(43));

    //Test Remove
    cout << endl;
    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: 20 40 10 70 99 -2 59 43 " << endl;
    intBST.remove(20);
    intBST.remove(40);
    intBST.remove(10);
    intBST.remove(70);
    intBST.remove(99);
    intBST.remove(-2);
    intBST.remove(59);
    intBST.remove(43);
    TestInsert(intBST.size(),intBST.getLeafCount(),
               intBST.getHeight(),intBST.empty());
    TestTraversals(intBST.getPreOrderTraversal(),intBST.getInOrderTraversal(),
                   intBST.getPostOrderTraversal());
    cout << endl;

    //Test insert again
    cout << "** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: 20 40 10 70 99 -2 59 43 " << endl;
    intBST.insert(20);
    intBST.insert(40);
    intBST.insert(10);
    intBST.insert(70);
    intBST.insert(99);
    intBST.insert(-2);
    intBST.insert(59);
    intBST.insert(43);
    TestInsert(intBST.size(),intBST.getLeafCount(),
               intBST.getHeight(),intBST.empty());
    TestTraversals(intBST.getPreOrderTraversal(),intBST.getInOrderTraversal(),
                   intBST.getPostOrderTraversal());
    cout << endl;

    //Display the TEST LEVEL & ANCESTORS
    cout << "** TEST LEVEL & ANCESTORS (again)**" << endl;
    TestLevelAncestors(intBST,-2,intBST.getLevel(-2),
                       intBST.getAncestors(-2));
    TestLevelAncestors(intBST,10,intBST.getLevel(10),
                       intBST.getAncestors(10));
    TestLevelAncestors(intBST,20,intBST.getLevel(20),
                       intBST.getAncestors(20));
    TestLevelAncestors(intBST,30,intBST.getLevel(30),
                       intBST.getAncestors(30));
    TestLevelAncestors(intBST,40,intBST.getLevel(40),
                       intBST.getAncestors(40));
    TestLevelAncestors(intBST,43,intBST.getLevel(43),
                       intBST.getAncestors(43));
    TestLevelAncestors(intBST,50,intBST.getLevel(50),
                       intBST.getAncestors(50));
    TestLevelAncestors(intBST,59,intBST.getLevel(59),
                       intBST.getAncestors(59));
    TestLevelAncestors(intBST,60,intBST.getLevel(60),
                       intBST.getAncestors(60));
    TestLevelAncestors(intBST,70,intBST.getLevel(70),
                       intBST.getAncestors(70));
    TestLevelAncestors(intBST,99,intBST.getLevel(99),
                       intBST.getAncestors(99));
    TestLevelAncestors(intBST,1,intBST.getLevel(1),
                       intBST.getAncestors(1));
    cout << endl;

    //Test Remove
    cout << "** TEST REMOVE (again)**" << endl;
    cout << "Removing in this order: -2 10 20 30 40 43 50 59 60 70 " << endl;
    intBST.remove(-2);
    intBST.remove(10);
    intBST.remove(20);
    intBST.remove(30);
    intBST.remove(40);
    intBST.remove(43);
    intBST.remove(50);
    intBST.remove(59);
    intBST.remove(60);
    intBST.remove(70);
    TestInsert(intBST.size(),intBST.getLeafCount(),
               intBST.getHeight(),intBST.empty());
    TestTraversals(intBST.getPreOrderTraversal(),intBST.getInOrderTraversal(),
                   intBST.getPostOrderTraversal());

    //Test Remove
    cout << endl;
    cout << "** TEST REMOVE (again)**" << endl;
    cout << "Removing in this order: 77 " << endl;
    intBST.remove(77);;
    TestInsert(intBST.size(),intBST.getLeafCount(),
               intBST.getHeight(),intBST.empty());
    TestTraversals(intBST.getPreOrderTraversal(),
                   intBST.getInOrderTraversal(),intBST.getPostOrderTraversal());
    cout << endl;

}


void strFile(){
    //Declare the variables
    ifstream infile;
    string strFile, strWord, word;

    BST<string> strBST;

    cout << "******************************" << endl;
    cout << "* STRING BINARY SEARCH TREE *" << endl;
    cout << "******************************" << endl << endl;

    cout << "** CREATE BST **" << endl;
    TestInsert(0,0,0,strBST.empty());

    cout << endl;

    cout << "Enter string file: ";
    cin >> strFile;
    cout << endl;

    infile.open(strFile);

    if(infile){
        while(getline(infile,strWord)){
            strBST.insert(strWord);
        }
        cout << endl;
    } else {
        cout << "Error opening file ...\n";
    }

    infile.close();

    //Display the TEST INSERT
    cout << "** TEST INSERT **" << endl;
    cout << "Inserting in this order: mary gene bea jen sue pat uma  " << endl;
    TestInsert(strBST.size(),strBST.getLeafCount(),
               strBST.getHeight(),strBST.empty());
    cout << endl;

    //Display the COPY CONSTRUCTOR
    testCopyConstructor(strBST);

    //Display the TEST ASSIGNMENT OPERATOR
    testAssignmentOperator(strBST);

    //Display the TEST TRAVERSALS
    cout << "** TEST TRAVERSALS **" << endl;
    TestTraversals(strBST.getPreOrderTraversal(),
                   strBST.getInOrderTraversal(),strBST.getPostOrderTraversal());
    cout << endl;

    //Display the TEST LEVEL & ANCESTORS
    cout << "** TEST LEVEL & ANCESTORS **" << endl;
    TestLevelAncestors(strBST,word = "mary",
                       strBST.getLevel("mary"),
                       strBST.getAncestors("mary"));
    TestLevelAncestors(strBST, word ="gene",
                       strBST.getLevel("gene"),
                       strBST.getAncestors("gene"));
    TestLevelAncestors(strBST,word="bea",
                       strBST.getLevel("bea"),
                       strBST.getAncestors("bea"));
    TestLevelAncestors(strBST,word="jen",
                       strBST.getLevel("jen"),
                       strBST.getAncestors("jen"));
    TestLevelAncestors(strBST, word ="sue",
                       strBST.getLevel("sue"),
                       strBST.getAncestors("sue"));
    TestLevelAncestors(strBST,word="pat",
                       strBST.getLevel("pat"),
                       strBST.getAncestors("pat"));
    TestLevelAncestors(strBST, word="uma",
                       strBST.getLevel("uma"),
                       strBST.getAncestors("uma"));
    TestLevelAncestors(strBST, word = "lisa",
                       strBST.getLevel("lisa"),
                       strBST.getAncestors("lisa"));

    //Test contains
    cout << endl;
    cout << "** TEST CONTAINS **" << endl;
    TestContains(strBST, word ="gene",
                 strBST.contains("gene"));
    TestContains(strBST, word ="mary",
                 strBST.contains("mary"));
    TestContains(strBST, word ="bea",
                 strBST.contains("bea"));
    TestContains(strBST,word ="uma",
                 strBST.contains("uma"));
    TestContains(strBST,word = "yan",
                 strBST.contains("yan"));
    TestContains(strBST, word ="amy",
                 strBST.contains("amy"));
    TestContains(strBST,word="ron",
                 strBST.contains("ron"));
    TestContains(strBST, word = "opal",
                 strBST.contains("opal"));

    //TEST REMOVE
    cout << endl;
    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: gene mary bea uma yan amy ron opal" <<endl;
    strBST.remove("gene");
    strBST.remove("mary");
    strBST.remove("bea");
    strBST.remove("uma");
    strBST.remove("yan");
    strBST.remove("amy");
    strBST.remove("ron");
    strBST.remove("opal");
    TestInsert(strBST.size(),strBST.getLeafCount(),
               strBST.getHeight(),strBST.empty());
    TestTraversals(strBST.getPreOrderTraversal(),
                   strBST.getInOrderTraversal(),strBST.getPostOrderTraversal());

    cout << endl;

    //Test insert again
    cout << "** TEST INSERT (again) **" << endl;
    cout << "Inserting in this order: gene mary bea uma yan amy ron opal"<<endl;
    strBST.insert("gene");
    strBST.insert("mary");
    strBST.insert("beau");
    strBST.insert("uma");
    strBST.insert("yan");
    strBST.insert("amy");
    strBST.insert("ron");
    strBST.insert("opal");
    TestInsert(strBST.size(),strBST.getLeafCount(),
               strBST.getHeight(),strBST.empty());
    TestTraversals(strBST.getPreOrderTraversal(),strBST.getInOrderTraversal(),
                   strBST.getPostOrderTraversal());
    cout << endl;

    //Display the TEST LEVEL & ANCESTORS
    cout << "** TEST LEVEL & ANCESTORS (again) **" << endl;
    TestLevelAncestors(strBST,word = "amy",
                       strBST.getLevel("amy"),
                       strBST.getAncestors("amy"));
    TestLevelAncestors(strBST,word="beau",
                       strBST.getLevel("beau"),
                       strBST.getAncestors("beau"));
    TestLevelAncestors(strBST, word ="gene",
                       strBST.getLevel("gene"),
                       strBST.getAncestors("gene"));
    TestLevelAncestors(strBST, word ="opal",
                       strBST.getLevel("opal"),
                       strBST.getAncestors("opal"));
    TestLevelAncestors(strBST,word = "mary",
                       strBST.getLevel("mary"),
                       strBST.getAncestors("mary"));
    TestLevelAncestors(strBST,word="jen",
                       strBST.getLevel("jen"),
                       strBST.getAncestors("jen"));
    TestLevelAncestors(strBST, word ="ron",
                       strBST.getLevel("ron"),
                       strBST.getAncestors("ron"));
    TestLevelAncestors(strBST, word ="yan",
                       strBST.getLevel("yan"),
                       strBST.getAncestors("yan"));
    TestLevelAncestors(strBST, word="uma",
                       strBST.getLevel("uma"),
                       strBST.getAncestors("uma"));
    TestLevelAncestors(strBST, word ="sue",
                       strBST.getLevel("sue"),
                       strBST.getAncestors("sue"));
    TestLevelAncestors(strBST,word="pat",
                       strBST.getLevel("pat"),
                       strBST.getAncestors("pat"));
    TestLevelAncestors(strBST, word = "lisa",
                       strBST.getLevel("lisa"),
                       strBST.getAncestors("lisa"));

    //TEST REMOVE
    cout << endl;
    cout << "** TEST REMOVE (again)**" << endl;
    cout << "Removing in this order: amy beau gene jen mary opal pat "
            "ron sue uma" <<endl;
    strBST.remove("amy");
    strBST.remove("beau");
    strBST.remove("gene");
    strBST.remove("jen");
    strBST.remove("mary");
    strBST.remove("opal");
    strBST.remove("pat");
    strBST.remove("ron");
    strBST.remove("sue");
    strBST.remove("uma");
    TestInsert(strBST.size(),strBST.getLeafCount(),
               strBST.getHeight(),strBST.empty());
    TestTraversals(strBST.getPreOrderTraversal(),strBST.getInOrderTraversal(),
                   strBST.getPostOrderTraversal());

    //TEST REMOVE
    cout << endl;
    cout << "** TEST REMOVE (again)**" << endl;
    cout << "Removing in this order: john" <<endl;
    strBST.remove("john");
    TestInsert(strBST.size(),strBST.getLeafCount(),
               strBST.getHeight(),strBST.empty());
    TestTraversals(strBST.getPreOrderTraversal(),strBST.getInOrderTraversal(),
                   strBST.getPostOrderTraversal());

}

void TestInsert(int numNodes,int numLeafs,int numHeight, bool isEmpty){
    cout << "# of nodes: " << numNodes << endl;
    cout << "# of leaves: " << numLeafs << endl;
    cout << "BST height: " << numHeight << endl;

    if(isEmpty == true){
        cout << "BST empty? true" <<endl;
    } else {
        cout << "BST empty? false" <<endl;
    }
}

void TestTraversals(string preOrder, string inOrder, string postOrder){
    cout << "pre-order: " << preOrder << endl;
    cout << "in-order: " << inOrder << endl;
    cout << "post-order: " << postOrder << endl;
}

template <typename T>
void TestLevelAncestors(BST<T> & bstTree, T value, int level, string ancestors){
    cout << "Level(" << value << "): " << level << ", ancestors(" << value
         << "): " << ancestors << endl;

}

template <typename T>
void TestContains(BST<T> & bstTree,T value, bool isContain){
    if(isContain == true){
        cout << "contains(" << value << "): " << "true" << endl;
    } else{
        cout << "contains(" << value << "): " << "false" << endl;
    }

}

template <typename T>
void testCopyConstructor(BST<T> & copyBSTTree){
    cout << "** TEST COPY CONSTRUCTOR **" << endl;
    BST<T> copyBST(copyBSTTree);
    TestInsert(copyBST.size(),copyBST.getLeafCount(),
               copyBST.getHeight(), copyBST.empty());
    TestTraversals(copyBST.getPreOrderTraversal(),copyBST.getInOrderTraversal(),
                   copyBST.getPostOrderTraversal());
    cout << endl;
}

template <typename T>
void testAssignmentOperator(BST<T> & operatorBSTTree){
    cout << "** TEST ASSIGNMENT OPERATOR (=) **" << endl;
    BST<T> operatorBST;
    operatorBST = operatorBSTTree.operator=(operatorBSTTree);
    TestInsert(operatorBST.size(),operatorBST.getLeafCount(),
               operatorBST.getHeight(), operatorBST.empty());
    TestTraversals(operatorBST.getPreOrderTraversal(),
                   operatorBST.getInOrderTraversal(),
                   operatorBST.getPostOrderTraversal());
    cout << endl;
}

