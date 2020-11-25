/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p3;

/**
 * This is the Generic Linked list queue that accepts
 * any type of payload.
 *
 * @param <E> Represent the type of an element
 * @author Bao Tran Do
 * @version 1.0
 */
public class Queue<E> {

    /**
     * This Node class <E> element and
     * a reference to the next node
     *
     * @author Bao Tran Do
     * @version 1.0
     */
    private class Node {
        //Takes generic type as input data
        public E value;
        //The Nodes references
        public Node next, prev;

        /**
         * Constructor that takes in RenderCommand, previous and next Nodes,
         * arguments.
         * @param render The reference to RenderCommand
         * @param prev The reference to the previous node
         * @param next The reference to the next node
         */
        public Node(E render, Node prev, Node next) {
            this.value = render;
            this.prev = prev;
            this.next = next;
        }
    }

    //A head reference
    private Node head;
    //A tail reference
    private Node tail;

    /**
     * No argument constructor
     */
    public Queue(){
        head = null;
        tail = null;
    }

    /**
     * Enqueue all the elements from another queue onto this queue.
     * @param other the queue with the elements to enqueue
     */
    public void append(Queue other) {

        for (Node p = other.head; p != null; p = p.next) {
            enqueue(p.value);
        }
    }

    /**
     * Make a deep copy of the queue.
     * @return the new queue you created.
     */
    public Queue<E> copy() {
        Queue theCopy = new Queue();

        //Create a node reference to the head
        Node currentNode = head;

        //If it is not null enqueue that to theCopy
        while(currentNode != null){
            theCopy.enqueue(currentNode.value);
            currentNode = currentNode.next;
        }
        return theCopy;
    }

    /**
     * Remove an element from the front of the queue.
     * @return oldest element's payload
     * @throws IllegalArgumentException When there is no element
     */
    public E dequeue() {

        if (head == null) {
            throw new IllegalArgumentException("cannot dequeue from "
                    + "empty queue");
        }

        E render = head.value;

        //setting head to the next element
        head = head.next;
        if(head == null){
            tail = null;
        }
        return render;
    }

    /**
     * Adding an element to the end of the queue.
     * @param render new element's payload
     */
    public void enqueue(E render) {
        //when tail is not null add the element
        if(tail != null) {
            tail.next = new Node(render, null, null);
            tail = tail.next;
        } else {
            tail = new Node(render, null, null);
            head = tail;
        }
    }

    /**
     * String representation of the queue contents.
     *
     * @return the string representation
     */
    public String toString() {
        StringBuilder s = new StringBuilder();

        //Traversal the list and append all values
        Node current = head;
        s.append("| ");
        while(current != null){
            s.append(current.value + " | ");
            current = current.next;
        }
        return s.toString();
    }

    /**
     * This empty method returns true if the queue is empty
     *
     * @return true if the queue is empty
     */
    public boolean empty() {
        return head == null;
    }

    /**
     * Returns the item at front(head) of queue.
     * @return item at head of queue (the first thing in)
     * @throws IllegalArgumentException user tries to peek at an empty queue
     */
    public E peek() {
        //holds item at head of queue
        E queueTop;
        //when user tries to peek at an empty queue
        if (head == null)
            throw new IllegalArgumentException("You can't pop an empty queue, "
                    + "Silly!");
        else {
            queueTop = head.value;
            return queueTop;
        }
    }

    /**
     * This equals method compare two objects contents.
     * Return true if one of the value are the same
     * for both of the objects.
     *
     * @param q2 The object reference to the Queue  class
     * @return true if have at least one value the same
     */
    public boolean equals(Queue<E> q2) {

        //Traversal the older list
        Node currentOlder = head;
        Node currentYounger = q2.head;
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


