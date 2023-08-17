// Bao Tran Do
// File: HuffmanTree.cpp
// November 14, 2020
// Purpose: This implementation is for the HuffmanTree described HuffmanTree.h

#include "HuffmanTree.h"

////REMOVE later
#include <string>
using namespace std;

bool HuffmanTree::createCodeTree(string filename) {
    std::priority_queue<
                            BST<CharFreq>::BSTNode*,
                            std::vector<BST<CharFreq>::BSTNode*>,
                            BST<CharFreq>::FrequencyCompare
                        > myPriorityQ;

    string str;
    string allText = "";
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {    // To get you all the lines.
        getline(infile,str); // Saves the line in STRING.
        allText += str + "\n";
    }
    infile.close();
    
    // **************************************************************
    // TODO: createCodeTree - add code here
    //  1. Count occurrences of every letter or symbol that you care about in
    //     allText (consider spaces ' ', newlines '\n', periods, commas,question
    //     marks, quotation marks, etc.
    //  2. Use myPriorityQ to build a tree, as described in the assignment.
    //  3. Set root (inherited from BST) to the final item in myPriorityQ
    //     (in other words, when there is a single tree in myPriorityQ).
    // **************************************************************

    ////Part 1
    const int ASCII= 256;
    vector<BST<CharFreq>::BSTNode*> charFreqVect(ASCII);

    //create the initialize storage for the ASCII
    for(int i =0; i  < (int)charFreqVect.size(); i++) {
        CharFreq cf((unsigned char)(i),0);
        BST<CharFreq>::BSTNode * tempNode =  new BST<CharFreq>::BSTNode(cf);
        charFreqVect[i] = tempNode;
    }

    //Count the frequency
    for(int i = 0; i < (int)allText.length(); i++) {
        int charValue = (unsigned int)(allText.at(i));
        charFreqVect[charValue]->data.frequency++;
    }

    ////part2: building the tree
    for (int i = 0; i < (int)charFreqVect.size();i++) {
        if(charFreqVect[i]->data.frequency >0) {
            myPriorityQ.push(charFreqVect[i]);
        }
    }

    //Create the temporary nodes to store the priority top and CharFreq
    BST<CharFreq>::BSTNode * temp1;
    BST<CharFreq>::BSTNode * temp2;
    CharFreq tempChar;

    while(myPriorityQ.size() > 1){

        temp1 = myPriorityQ.top();
        myPriorityQ.pop();
        temp2 = myPriorityQ.top();
        myPriorityQ.pop();

        tempChar.frequency = temp1->data.frequency
                             +temp2-> data.frequency;

        BST<CharFreq>::BSTNode * newTempNode =
                new BST<CharFreq>::BSTNode(tempChar);

        // don't want to lose the children,
        // need to keep track it and connect it to the new node
        newTempNode->left = temp1;
        newTempNode->right = temp2;

        myPriorityQ.push(newTempNode);
    }

    ////part 3
    root = myPriorityQ.top();

    return true;
}

bool HuffmanTree::encodeFile(string originalFilename, string outputFilename) {
    string str;
    string allText = "", currentStream = "";
    ifstream infile;
    const int WRITE_SIZE = 8;

    infile.open(originalFilename.c_str());
    if( !infile.is_open() ) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {        // To get you all the lines.
        getline(infile, str);   // Saves the line in string.
        allText += str + "\n";
    }
    infile.close();
    
    std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
    if (!outStream.is_open()) {
        cout << "ERROR creating output file!\n";
        return false;
    }

    //set the encode to the letter
    string ss;
    traverseEncoding(root,ss);

    for (int i = 0; i < (int)allText.length(); i++) {
        // TODO: encodeFile - add your code here
        //  add the appropriate encoding for allText[i] to currentStream

        string str = "";
        //retrieving the character Huffman's encoded
        charEncoding(root,allText[i],str);

        currentStream += str;

        // **************************************************************
        
        while ((int)currentStream.length() >= WRITE_SIZE) {
            string byte = currentStream.substr(0, WRITE_SIZE);
            bitset<8> set(byte);
            const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
            outStream.write(&toWrite,sizeof(char));
            currentStream = currentStream.substr(WRITE_SIZE, 
                                    currentStream.length()- WRITE_SIZE );
        }
    }

    outStream.close();
    return false;
}

//find that char and return the encoded
void HuffmanTree::charEncoding(BSTNode * ptr, unsigned char c, string & str){

    //check left node
    if(ptr->left != nullptr) {
        charEncoding(ptr->left, c, str);
    }

    //checking right node
    if(ptr->right  != nullptr){
        charEncoding(ptr->right,c, str);
    }

    //once the node the char is found at that data.letter return the encoding
    if(ptr->data.letter == c) {
        str = ptr->data.encoding;
    }
}

//encoded setting
void HuffmanTree::traverseEncoding(BSTNode *& ptr, string encoding){

    string left = "0";
    string right = "1";

    if(ptr->left == nullptr && ptr->right == nullptr){
        ptr->data.encoding = encoding;

    }

    //check left node
    if(ptr->left != nullptr){
        traverseEncoding(ptr->left,encoding + left);
    }

    //checking right node
    if(ptr->right != nullptr){
        traverseEncoding(ptr->right,encoding + right);
    }
}


bool HuffmanTree::decodeFile(string filename) {
    int i = 0; string bitStream = "";
    ifstream encodedfile;

    encodedfile.open(filename.c_str(), ios::binary);
    if (!encodedfile.is_open()) {
        cout << "ERROR opening encoded file!\n";
        return false;
    }    

    encodedfile >> std::noskipws;
    while (!encodedfile.eof()) {
        unsigned char readMe;
        encodedfile >> readMe;
        bitset<8> set((unsigned long)readMe);
        bitStream += set.to_string();
    }
    
    encodedfile.close();
    cout << "**************************************************************\n";
    cout << "Decoding: " << endl;
    while (i != -1)
        i = traverseAndPrint(bitStream, i);
    return false;
}

int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur) {
  if(i >= (int)bits.length())
        return -1;
    // **************************************************************
    // TODO: traverseAndPrint - add your code here
    //  Write this function using recursion. This is essentially your decode
    //  function.  You need to step through the tree based on reading 0 or 1
    //  and when you reach a leaf, print (using cout) the appropriate character.
    //  - i represents your current location in the string
    //  - cur represents the cur node in your tree
    //  Don't forget that you need to keep going after printing out a character 
    //  (which means restarting at the top of the tree)
    // **************************************************************
    int increment = 1;
    char left = '0';
    char right = '1';

    if(cur != nullptr){
        if(cur->right == nullptr && cur->left == nullptr) {
            cout << cur->data.letter;
            return traverseAndPrint(bits,i,root);
        }

        if(bits.at(i) == left){
            return traverseAndPrint(bits,i + increment,cur->left);
        }

        if(bits.at(i) == right) {
            return traverseAndPrint(bits,i + increment,cur->right);
        }

    }
    return -1;
}

void HuffmanTree::displayCode(ostream &out) {
    // **************************************************************
    // TODO: displayCode - add your code here
    //  Print out each letter and its code, you might want to check for
    //  special cases (space, newline, etc.)
    out << endl << endl;
    out << "**************************************************************\n";
    out << endl;
    out << "Displaying each letter and its code: " << endl;
    preOrderCode(root,out);

}

void HuffmanTree::preOrderCode(BSTNode * ptr, ostream &out ){

    if(ptr->right == nullptr && ptr->left == nullptr) {
        out << " letter: " << ptr->data.letter
        <<  "      Huffman Code: " <<  ptr->data.encoding << endl;
    }

    //check left node
    if(ptr->left != nullptr) {
        preOrderCode(ptr->left,out);
    }

    //check right node
    if(ptr->right != nullptr){
        preOrderCode(ptr->right,out);
    }
}

ostream& operator<<(ostream &out, HuffmanTree &code) {
    code.displayCode(out);
    return out;
}


