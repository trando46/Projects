// Bao Tran Do
// File LinkedList.h
// October 12, 2020
// Specification file for the LinkedList class used to populate any data types
//     (since this is a a template class) for nodes to create the LinkedList.

#ifndef LAB4_TESTING_LINKEDLIST_H
#define LAB4_TESTING_LINKEDLIST_H


#include <string>
#include <sstream>
using namespace std;

template <typename T>
class LinkedList {

public:

    LinkedList();
    // Constructor that initializes the node to nullptr
    // precondition: the node is not yet initialize
    // postcondition: the node is now initialize to nullptr

    ~LinkedList();
    // Destructor that deallocate the node
    // precondition: the node that is allocated
    // postcondition: deallocate the node

    void appendNode(T);
    // This method append node to the list in the order that it is entered in
    // precondition: the list is empty
    // postcondition: there are contents in the list

    void insertNode(T);
    // This method insert the list from smallest to largest in order
    // precondition: the list is unorganized
    // postcondition: organize the value from smallest to largest in order

    void deleteNode(T);
    // This method removed a particular value from the list and assigned the
    // pointer from predecessor to the node with that value successor
    // precondition: the value is present
    // postcondition: the value is removed

    T getLastNegative();
    // This method return the last negative entered from the list that is
    // entered in order (the list is not yet sorted, thus, unorganized)
    // precondition: none
    // postcondition: return the last negative number that is entered

    string to_string() const;
    // Returns the string representation of the LinkedList class
    // precondition: none
    // postcondition: returns the string representation

private:

    struct Node {
        T data;
        Node * next;
    };        // struct to hold the node and the data type

    Node * head;    //Creating the node head

    T getLastNegative(Node * ptr, T &); // Pass in the node as argument and
    // perform the recursive call
};

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node * curr;
    while (head != nullptr) {
        curr = head;
        head = head->next;
        delete curr;
    }
}

template <typename T>
void LinkedList<T>::appendNode(T d) {
    Node * curr;	// helper Node that allows me to traverse the list
    Node * newNode = new Node;
    newNode->data = d;
    newNode->next = nullptr;

    if (head == nullptr)
        head = newNode;
    else {
        curr = head;
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode;
    }
}

template <typename T>
void LinkedList<T>::insertNode(T d) {
    Node * curr;
    Node * prev;
    Node * newNode = new Node;
    newNode->data = d;

    if (head == nullptr) {
        head = newNode;
        newNode->next = nullptr;
    } else {
        prev = nullptr;
        curr = head;
        while (curr != nullptr && curr->data < d) {
            prev = curr;
            curr = curr->next;
        }
        // add to beginning of list; otherwise, end or between nodes
        if (prev == nullptr) {
            head = newNode;
            newNode->next = curr;
        } else {
            prev->next = newNode;
            newNode->next = curr;
        }
    }
}

template <typename T>
void LinkedList<T>::deleteNode(T d) {
    Node * curr;
    Node * prev;
    if (head != nullptr) {
        if (head->data == d) {
            curr = head;
            head = head->next;
            delete curr;
        } else {
            curr = head;
            while (curr != nullptr && curr->data != d) {
                prev = curr;
                curr = curr->next;
            }
            // only delete if d is in the list
            if (curr != nullptr) {
                prev->next = curr->next;
                delete curr;
            }
        }
    }
}

template <typename T>
string LinkedList<T>::to_string() const {
    stringstream ss;
    Node * curr = head;
    while (curr != nullptr) {
        ss << curr->data << " ";
        curr = curr->next;
    }
    ss << "\n";
    return ss.str();
}

template <typename T>
T LinkedList<T>::getLastNegative() {

    // Create a temporary node
    Node * temp = head;

    // Set the initial value of the head
    T lastNegative = temp->data;

    //start the recursive call by calling the helper function
    return getLastNegative(temp,lastNegative);
}

template <typename T>
T LinkedList<T>::getLastNegative(Node *ptr, T & lastNegative) {
    // Declare and instantiate the minimum value to be 0
    // anything less than 0 is a negative number
    int min = 0;

    // If the node is not null then enter the loop
    if (ptr != nullptr) {

        //If the node is negative then assign it to the variable lastNegative
        if (ptr->data < min) {
            lastNegative = ptr->data;
        }
        //Recursive call
        getLastNegative(ptr->next, lastNegative);
    }
    //Return the very last negative number
    return lastNegative;
}

#endif //LAB4_TESTING_LINKEDLIST_H
