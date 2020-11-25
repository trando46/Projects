// Bao Tran Do
// File: HashTable.h
// November 10, 2020
// Specification file for the HashTable.h used to populate an array with
//      the key and value for the HashTable

#ifndef LAB6_HASHTABLE_H
#define LAB6_HASHTABLE_H
#include <sstream>
using namespace std;


class HashTable {
public:
    HashTable(int capacity);
    // Constructor that initializes the variables and pass in the capacity size
    // of the Bucket
    // precondition: not yet initialize
    // postcondition: the Bucket is now initialize and tableSize & memberCount
    ~HashTable();
    // Destructor that deallocate the Bucket
    // precondition: the Bucket that is allocated
    // postcondition: deallocate the Bucket
    int put(int key, int value);
    // This method associates the specified value with the specified key in the
    // HashTable. Collisions are resolved using linear probing.
    // precondition: empty buckets
    // postcondition: the buckets are now filled based on the formula
    int get(int key);
    // This method returns the value to which the specified key is mapped, or -1
    // if this HashTable contains no mapping for the key.
    // precondition: none
    // postcondition: return the value or -1
    bool contains(int key);
    // Returns true if this HashTable contains a mapping for the specified key.
    // precondition: none
    // postcondition: return true if condition is met
    int size();
    // Returns the number of unique keys stored in the table
    // precondition: none
    // postcondition: returns the number of elements
    bool empty();
    // Returns true if the HashTable is empty
    // precondition: none
    // postcondition: return true if the table is empty
private:
    struct Bucket {
        int key;
        int value;
    };


    Bucket * hashArr;   // 1D dynamic array to hold the buckets
    int memberCount;    // keeps track of the members in the array
    int tableSize;      // The array(table) size

    // add private helper methods and attributes
    int linearProbing(int, int &, int);
    // Helper method for the put method.
    // This method perform the linear probing of the collision strategy #1 that
    // takes in the key, the index of where that key is located and probing
    // precondition: empty buckets
    // postcondition: the buckets are now filled based on the formula

    int contains(int,int &);
    // Helper method for contain. Return the index value of the key.
    // Returns true if this HashTable contains a mapping for the specified key.
    // precondition: none
    // postcondition: return true if condition is met
    void resize();
    // Resize the array when it is full
    // precondition: not resized
    // postcondition: size is now double in the array

};

HashTable::HashTable(int capacity) {

    hashArr = new Bucket[capacity];
    tableSize = capacity;
    memberCount = 0;
}

HashTable::~HashTable() {
    delete [] hashArr;
}

int HashTable::put(int key, int value) {

    int previousValue, index = 0, probing = 0;
    contains(key,index);

    if(memberCount >= tableSize){
        //call the resize function
        resize();
    }

    if(index != -1){
        //If the HashTable previously contained a mapping for the key
        // replace the old value with the new one
        previousValue = hashArr[index].value;
        hashArr[index].value = value;
        return previousValue;
    } else {
        //Assuming the key doesnt exist and there was no mapping for key and
        //looking for the next empty space to place it
        linearProbing(key,index,probing);
        hashArr[index].key = key;
        hashArr[index].value = value;
        memberCount++;
        return -1;
    }
}

int HashTable::linearProbing(int key, int & index, int probing) {

    //Use collision strategy # 1
    // h(key) = (h(key) + f(i)) % tableSize
    index = (key + probing) % tableSize;

    if(hashArr[index].key == 0 && hashArr[index].value == 0
        && tableSize > index){
        return index;
    } else {
        probing++;
        linearProbing(key,index,probing);
    }
    return -1;
}

int HashTable::get(int key) {

   int index = 0;
   contains(key,index);

   if(index == -1){
       return -1;
   } else {
       return hashArr[index].value;
   }
}

bool HashTable::contains(int key) {
    int index = 0;
    contains(key, index);

    if(empty()){
        return false;
    } else {
        if(index == -1){
            //key not found at that index
            return false;
        } else {
            //key found at that index
            return true;
        }
    }

}

int HashTable::contains(int key, int & index){
    //Traverse through the entire array
    for(int i = 0; i < tableSize; i++){
        //if the key is found return the index where the key is located
        if(hashArr[i].key > 0 && hashArr[i].key == key) {
            index = i;
            return index;
        }
    }
    //if key not found return index at -1
    return index = -1;
}


int HashTable::size(){
    return memberCount;
}

bool HashTable::empty() {
    return memberCount == 0;

}

void HashTable::resize() {
    // update capacity
   tableSize *= 2;

    // create new array based on updated capacity
    Bucket * tempArr = new Bucket[tableSize];

    // copy old array values to new array
    for (int i = 0; i < memberCount; i++)
        tempArr[i] = hashArr[i];

    // delete old array
    delete [] hashArr;

    // reassign old array to new array
    hashArr = tempArr;
}



#endif //LAB6_HASHTABLE_H
