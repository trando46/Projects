// Bao Tran Do
// File: BST.h
// October 19, 2020
// Specification file for the BST class used to populate any data types
//      (this a template class) for nodes to create the binary search tree.

#ifndef P2_BSTx_H
#define P2_BSTx_H
#include <sstream>
#include <queue>
using namespace std;

template <typename T>
class BST {

public:
    BST();
    // Constructor that initializes the node to nullptr
    // precondition: the node is not yet initialize
    // postcondition: the node is now initialize to nullptr
    ~BST();
    // Destructor that deallocate the node
    // precondition: the node that is allocated
    // postcondition: deallocate the node
    BST(const BST &);
    // Copy constructor to perform a deep copy of the tree
    // precondition: the tree is allocated
    // postcondition: deallocate the tree
    BST& operator=(const BST &); //Overloaded = operator
    // Overloaded assignment operator that assigns the BST passed in as a
    // parameter to an existing BST
    // precondition: deallocate the tree
    // postcondition: perform deep copy
    bool contains(T);
    // Searches the BST to determine if a given value is present
    // precondition: none
    // postcondition: Return true if the value is found or else false
    void insert(T);
    // Inserts the element passed in as a parameter into the BST. Must use
    // recursion
    // precondition: the list is empty
    // postcondition: there are contents in the tree
    void remove(T);
    // Removes the specified value from the BST
    // precondition: the value is still in the tree
    // postcondition: the value is no longer present
    bool empty() const;
    // Determines if the BST is empty or not
    // precondition: none
    // postcondition: return true if the tree is empty
    string getPreOrderTraversal();
    // Returns a string of elements in the order specified by the pre-order
    // traversal of the BST
    // precondition: the tree is not organized.
    // postcondition: return the pre-order traversal of the tree
    string getPostOrderTraversal();
    // Returns a string of elements in the order specified by the post-order
    // traversal of the BST
    // precondition: the tree is not organized.
    // postcondition: return the post-order traversal of the tree
    string getInOrderTraversal();
    // Returns a string of elements in the order specified by the in-order
    // traversal of the BST
    // precondition: the tree is not organized.
    // postcondition: return the in-order traversal of the tree
    int getLeafCount();
    // Returns the count of nodes in the BST that do not have any children
    // precondition: none
    // postcondition: return the nodes in the BST that do not have children
    int getHeight();
    // Returns the height of the BST. The height is the number of levels it
    // contains.
    // precondition: none
    // postcondition: returns the height of the tree
    int size();
    // Returns the total number of nodes in the tree
    // precondition: none
    // postcondition: returns the total number of the nodes in the tree
    int getLevel(T);
    // Returns the level of a node in the BST. If the node with the given value
    // is not present in the BST, returns -1.
    // precondition: none
    // postcondition: returns the level of a node from the tree
    string getAncestors(T);
    // Returns a string of elements that are the ancestors(s) of the given node
    // The most immediate ancestor will be the first in the list. If the value
    // is not present in the tree, returns an empty string
    // precondition: none
    // postcondition: returns the ancestor(s) of the element
    int getWidth();
    // Returns the max width of the tree. The width is the largest number of
    // nodes in the same level
    // precondition: none
    // postcondition: returns the max width of the tree
    string getLevelOrder();
    // Returns a string that results from traversing the BST level by level
    // precondition: none
    // postcondition: return a string of values from traversing each level.

private:
    struct Node {
        T data;
        Node * left;
        Node * right;
    };          // Node to hold the the data type and the left and right node
    Node * root;    // Creating the node root

    string getPreOrderTraversal(Node *,stringstream &);
    // Helper method for getPreOrderTraversal. Returns a string of elements in
    // the order specified by the pre-order traversal of the BST in recursion
    // Takes in a node and stringstream reference
    // precondition: the tree is not organized.
    // postcondition: return the pre-order traversal of the tree
    string getPostOrderTraversal(Node *, stringstream &);
    // Helper method for getPostOrderTraversal Returns a string of elements in
    // the order specified by the post-order traversal of the BST in recursion
    // Takes in a node and stringstream reference
    // precondition: the tree is not organized.
    // postcondition: return the post-order traversal of the tree
    string getInOrderTraversal(Node *, stringstream &);
    // Helper method for getInOrderTraversal. Returns a string of elements in
    // the order specified by the in-order traversal of the BST in recursion
    // Takes in a node and stringstream reference
    // precondition: the tree is not organized.
    // postcondition: return the in-order traversal of the tree
    string getAncestors(Node *,T ,stringstream &);
    // Helper method for getAncestors. Returns a string of elements that are the
    // ancestors(s) of the given node. The most immediate ancestor will be the
    // first in the list. If the value is not present in the tree,
    // returns an empty string. Takes in a node, an element, and stringstream
    // reference
    // precondition: none
    // postcondition: returns the ancestor(s) of the element
    int getLeafCount(Node *, int &);
    // Helper method for getLeafCount. Returns the count of nodes in the BST
    // that do not have any children. Takes in a node and the reference of the
    // leaf count
    // precondition: none
    // postcondition: return the nodes in the BST that do not have children
    int getHeight(Node *, int &);
    // Helper method for getHeight. Returns the height of the BST. The height is
    // the number of levels it contains. Takes in a node and the reference
    // of the height
    // precondition: none
    // postcondition: returns the height of the tree
    int size(Node *, int &);
    // Helper method for the size. Returns the total number of nodes in the tree
    // Takes in a node and a reference of the size
    // precondition: none
    // postcondition: returns the total number of the nodes in the tree
    int getLevel(Node *, T ,int &);
    // Helper method for getLevel. Returns the level of a node in the BST. If
    // the node with the given value is not present in the BST, returns -1.
    // Takes in a node, value, and a reference of the level
    // precondition: none
    // postcondition: returns the level of a node from the tree
    bool contains(Node * , T , bool & , bool & );
    // Helper method for contains. Searches the BST to determine if a given
    // value is present. Takes in one node, an element, and a boolean for the
    // left side of the tree and the right side of the tree
    // precondition: none
    // postcondition: Return true if the value is found or else false
    void insert(Node *&, Node *&);
    // Helper method for insert. Inserts the element passed in as a
    // parameter into the BST. Must use recursion. Takes in two nodes.
    // precondition: the list is empty
    // postcondition: there are contents in the tree
    void remove(Node *&, T);
    // Helper method for remove of the node. Removes the specified value from
    // the BST.  Takes in the node and a value.
    // precondition: the value is still in the tree
    // postcondition: the value is no longer present
    void makeDeletion(Node *&, T);
    // Helper method for remove of the node. Removes the specified value from
    // the BST. Delete the node of that value from the tree. Takes in the node
    // and a value.
    // precondition: the value is still in the tree
    // postcondition: the value is no longer present
    void destroyTree(Node *&);
    // Helper method destructor. Destructor that deallocate the node
    // precondition: the node that is allocated. Takes in the node.
    // postcondition: deallocate the node
    Node * deepCopy(Node * copiedTree);
    // Deep constructor helper method. Copy constructor to perform a deep copy
    // of the tree. Takes in the node and the reference.
    // precondition: the tree is allocated
    // postcondition: deallocate the tree
    int getWidth(Node *, int &);
    // Helper function for getWidth. Returns the max width of the tree.
    // The width is the largest number of nodes in the same level. Takes in a
    // node and a reference of an int.
    // precondition: none
    // postcondition: returns the max width of the tree
    string getLevelOrder(Node * ptr, stringstream &);
    // Helper function for getLevelOrder takes in a node, reference of
    // stringstream.
    // Returns a string that results from traversing the BST level by level
    // precondition: none
    // postcondition: return a string of values from traversing each level.
};

template <typename T>
BST<T>::BST() {
    root = nullptr;
}

template <typename T>
BST<T>::~BST() {
    destroyTree(root);
}


template <typename T>
BST<T>::BST(const BST & object){
    root = deepCopy(object.root);
}

template <typename T>
typename BST<T>::Node * BST<T>::deepCopy(Node * copyTree){
    Node * newCopiedTree = new Node;

    //check if root is null
    if(copyTree == nullptr){
        return nullptr;
    }else{
       newCopiedTree->data = copyTree->data;
       newCopiedTree->left = deepCopy(copyTree->left);
       newCopiedTree->right = deepCopy(copyTree->right);
    }
    return newCopiedTree;
}

template <typename T>
BST<T> & BST<T>::operator=(const BST & object){
    if(this != &object){
        //Deallocate the memory
        destroyTree(this->root);
        this->root = deepCopy(object.root);
    }
    return * this;
}

template <typename T>
bool BST<T>::empty() const{
    return root == nullptr;
}

template <typename T>
void BST<T>::destroyTree(Node *&ptr) {
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}

template <typename T>
bool BST<T>::contains(T item) {
    bool leftTree;
    bool rightTree;
    return contains(root,item,leftTree,rightTree);
}

template <typename T>
bool BST<T>::contains(Node * ptr, T item, bool & leftTree, bool & rightTree){
    if(ptr != nullptr){
        //base case
        if(ptr->data == item){
            return true;
        } else if ( item < ptr->data){
            leftTree = contains(ptr->left,item,leftTree,rightTree);
            if(leftTree == true){
                return true;
            }
        } else if (item > ptr->data){
            rightTree = contains(ptr->right,item,leftTree,rightTree);
            if (rightTree == true){
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void BST<T>::insert(T item) {
    Node * newNode = new Node;

    newNode->data = item;
    newNode->left = newNode->right = nullptr;

    insert(root, newNode);
}

template <typename T>
void BST<T>::insert(Node *& ptr, Node *& newNode) {
    if (ptr == nullptr)
        ptr = newNode;
    else if (ptr->data > newNode->data)
        insert(ptr->left, newNode);
    else
        insert(ptr->right, newNode);
}

template <typename T>
void BST<T>::remove(T item) {
    remove(root, item);
}

template <typename T>
void BST<T>::remove(Node *& ptr, T item) {
    if (ptr != nullptr) {
        if (ptr->data > item)
            remove(ptr->left, item);
        else if (ptr->data < item)
            remove(ptr->right, item);
        else
            makeDeletion(ptr, item);
    }
}

template <typename T>
void BST<T>::makeDeletion(Node *& ptr, T item) {
    Node * curr = nullptr;
    if (ptr != nullptr) {
        if (ptr->left == nullptr) {
            curr = ptr;
            ptr = ptr->right;
            delete curr;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr;
        } else {
            curr = ptr->right;
            while (curr->left != nullptr)
                curr = curr->left;
            ptr->data = curr->data;
            remove(ptr->right, curr->data);
        }
    }
}

template <typename T>
string BST<T>::getPreOrderTraversal() {
    stringstream ss;
    return getPreOrderTraversal(root, ss);
}
template <typename T>
string BST<T>::getPreOrderTraversal(Node * ptr, stringstream & ss) {
    if (ptr != nullptr) {
        ss << ptr->data << " ";
        getPreOrderTraversal(ptr->left,ss);
        getPreOrderTraversal(ptr->right,ss);
    }
    return ss.str();
}

template <typename T>
string BST<T>::getPostOrderTraversal() {
    stringstream ss;
    return getPostOrderTraversal(root, ss);
}

template <typename T>
string BST<T>::getPostOrderTraversal(Node * ptr, stringstream & ss) {
    if (ptr != nullptr) {
        getPostOrderTraversal(ptr->left,ss);
        getPostOrderTraversal(ptr->right,ss);
        ss << ptr->data << " ";
    }
    return ss.str();
}

template <typename T>
string BST<T>::getInOrderTraversal() {
    stringstream ss;
    return getInOrderTraversal(root, ss);

}
template <typename T>
string BST<T>::getInOrderTraversal(Node * ptr, stringstream & ss) {

    if (ptr != nullptr) {
        getInOrderTraversal(ptr->left,ss);
        ss << ptr->data << " ";
        getInOrderTraversal(ptr->right,ss);
    }
    return ss.str();
}

template <typename T>
int BST<T>::getLeafCount() {
    int leafCount = 0;
    getLeafCount(root, leafCount);
    return leafCount;
}

template <typename T>
int BST<T>::getLeafCount(Node * ptr, int & leafCount) {
    if(ptr != nullptr){
        if(ptr->left == nullptr && ptr->right == nullptr){
            return leafCount++;
        } else {
           return getLeafCount(ptr->left,leafCount) +
                getLeafCount(ptr->right,leafCount);
        }
    }
    return 0;
}

template <typename T>
int BST<T>::getHeight() {
    int heightCount = 0;
    return getHeight(root,heightCount);
}

template <typename T>
int BST<T>::getHeight(Node * ptr, int & heightCount){
    int rootLevel = 1;
    int leftDepth;
    int rightDepth;
    if(ptr != nullptr){

        leftDepth = getHeight(ptr->left,heightCount);
        rightDepth = getHeight(ptr->right,heightCount);

        if(rightDepth < leftDepth){
            return heightCount = leftDepth + rootLevel;
        } else {
            return heightCount = rightDepth + rootLevel;
        }
    }
    return 0;
}

template <typename T>
int BST<T>::size() {
    int sizeCount = 0;
    return size(root,sizeCount);
}

template <typename T>
int BST<T>::size(Node * ptr, int & sizeCount){
    int rootLevel = 1;
    int leftSize;
    int rightSize;
    if(ptr != nullptr){
        leftSize = size(ptr->left,sizeCount);
        rightSize = size(ptr->right,sizeCount);
        return sizeCount = leftSize + rootLevel + rightSize;
    }
    return 0;
}

template <typename T>
int BST<T>::getLevel(T value){
    int level = 0;
    return getLevel(root,value,level);
}

template <typename T>
int BST<T>::getLevel(Node * ptr, T value,int & level){
    bool contain = contains(value);
    if(ptr != nullptr){

        if(ptr->data == value){
            return level;
        }

        if(contain == true){
            if(value < ptr->data){   //Left subtree
                getLevel(ptr->left,value,++level);
                return level;
            } else if (value > ptr->data){ //Right subtree
                getLevel(ptr->right,value,++level);
                return level;
            }
        }
    }
    return -1;
}

template <typename T>
string BST<T>::getAncestors(T value) {
    stringstream ss;
    return getAncestors(root,value,ss);
}

template <typename T>
string BST<T>::getAncestors(Node * ptr, T value, stringstream & ss) {
    bool contain = contains(value);
    if (ptr != nullptr) {

        if(ptr->data == value){
            ss << "";
        }
        if(contain == true){
            if(value < ptr->data) { //Go to the far left first then print
                getAncestors(ptr->left,value,ss);
                ss << ptr->data << " ";
            } else if(value > ptr->data){ //Go to the far right first then print
                getAncestors(ptr->right,value,ss);
                ss << ptr->data << " ";
            }
        } else {
            ss << "";
        }
    }
    return ss.str();
}

template <typename T>
int BST<T>::getWidth(){
    int maxWidth = INT16_MIN, currentWidth;

    for(int level = 1; level <= getHeight(); level++) {
        currentWidth = getWidth(root, level);
        if (maxWidth < currentWidth ) {
            maxWidth = currentWidth;
        }
    }
    return maxWidth;
}

template <typename T>
int BST<T>::getWidth(Node * ptr, int & level){
    int rootLevel = 1, current = level - rootLevel, width;

    if(ptr != nullptr){
        if(level == rootLevel){
            return rootLevel;
        } else if (level > rootLevel) {
            width = getWidth(ptr->left,current) +
                    getWidth(ptr->right,current);
        }
        return width;
    }
    return 0;
}

template <typename T>
string BST<T>::getLevelOrder(){
    stringstream ss;
    getLevelOrder(root,ss);
    return ss.str();
}

template <typename T>
string BST<T>::getLevelOrder(Node * ptr, stringstream & ss){
    queue<Node *> queueNode;
    Node * currentNode;

    if(ptr != nullptr) {
        queueNode.push(ptr);
        queueNode.push(nullptr);

        while (queueNode.size() > 1) {
            currentNode = queueNode.front();

            if (currentNode != nullptr) {

                if (currentNode->left){
                    queueNode.push(currentNode->left);
                }
                if (currentNode->right) {
                    queueNode.push(currentNode->right);
                }
                ss << currentNode->data << " ";
            } else {
                queueNode.push(nullptr);
                ss << "";
            }
            queueNode.pop();
        }
    }
    return ss.str();
}

#endif //P2_BSTx_H





