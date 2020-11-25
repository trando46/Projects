/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p3;

/**
 * This a stack class of LinkedList that accepts generic types.
 * Methods throw an exception if popping from or peeking
 * into an empty stack.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class Stack<E> {

    /**
     * The Node class is used to implement the
     * linked list.
     *
     * @author Bao Tran Do
     * @version 1.0
     */
    private class Node {
        //Reference variable for the generic type
        E value;
        //Reference variable for the next Node
        Node next;

        /**
         * Node constructor take takes in two arguments
         * @param val The reference to the generic type
         * @param n The reference to the next node
         */
        Node(E val, Node n) {
            value = val;
            next = n;
        }
    }

    // Top of the stack
    private Node top;

    /**
     * No argument constructor
     */
    public Stack(){
        top = null;
    }

    /**
     * The size method determines the size of the list.
     * This is done by traversing the list and incrementing
     * a count for each node visited. Need this method
     * to know the discard stack size when the deal stack is
     * empty.
     *
     * @return The size of the list.
     */
    public int size() {
        int count  = 0;  //variable to keep count of nodes 
        Node p = top;
        while (p != null) {
            count++;  //increments the count if nodes exists 
            p = p.next;
        }
        return count;  //returns count 
    }

    /**
     * The empty method checks for an empty stack.
     *
     * @return true if stack is empty
     */
    public boolean empty() {
        return top == null;
    }


    /**
     * Make a deep copy of the Stack.
     * @return the new stack created for the copy.
     */
    public Stack<E> copy() {
        //Create a temporary object to copy the value from
        //first in first out
        Stack temporary = new Stack();

        //Create a node reference to the head
        Node currentNode = top;

        //If it is not null push that to temporary
        while(currentNode != null){
            temporary.push(currentNode.value);
            currentNode = currentNode.next;
        }

        //Create theCopy object to traverse the temporary
        //object so that is now becomes last in first out.
        Stack theCopy = new Stack();

        //Create a node reference to the head of the temporary object
        Node realCurrent = temporary.top;

        //If it is not null push that to temporary
        while(realCurrent != null){
            theCopy.push(realCurrent.value);
            realCurrent = realCurrent.next;
        }
        return theCopy;
    }

    /**
     * The push method adds a new item to the stack.
     *
     * @param p The item to be pushed onto the stack.
     */
    public void push(E p) {

        top = new Node(p, top);
    }

    /**
     * The Pop method removes the value at the
     * top of the stack.
     *
     * @return The value at the top of the stack.
     * @throws IllegalArgumentException When the
     * stack is empty.
     */
    public E pop() {
        if (empty()) {
            throw new IllegalArgumentException("cannot pop from "
                    + "empty stack");
        } else {
            E retValue = top.value;
            top = top.next;
            return retValue;
        }
    }

    /**
     * The peek method returns the top value on the stack.
     *
     * @return The value at the top of the stack.
     * @throws IllegalArgumentException When the
     * stack is empty.
     */
    public E peek() {
        if (empty()) {
            throw new IllegalArgumentException("cannot peek from "
                    + "empty stack");
        } else {
            return top.value;
        }
    }

    /**
     * The toString method computes a string
     * representation of the contents of the stack.
     *
     * @return The string representation of the
     * stack contents.
     */
    public String toString() {
        StringBuilder sBuilder = new StringBuilder();
        Node p = top;
        while (p != null) {
            sBuilder.append(p.value + " ");
            p = p.next;
        }
        return sBuilder.toString();
    }

    /**
     * This equals method compare two objects contents.
     * Return true if one of the value are the same
     * for both of the objects.
     * @param s1 The object reference to the Stack class
     * @return true if have at least one value the same
     */
    public boolean equals(Stack<E> s1){

        //Traversal the older list
        Node currentOlder = top;
        Node currentYounger = s1.top;
        while(currentOlder != null && currentYounger != null){
            //Compare older list content with the newer list
            if(currentOlder.value.equals(currentYounger.value)){
                return true;
            }
            currentOlder = currentOlder.next;
            currentYounger = currentYounger.next;
        }

        return false;
    }
}