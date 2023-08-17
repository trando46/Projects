/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p2;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * This MessageDecoder class is responsible for converting a scrambled message
 * file into plain text. The scrambled file must be scanned only once and
 * must be scanned inside this class. This class utilize the linked list data
 * structure to accomplish the decoding work and does not call any methods
 * of SecreteMessage class.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class MessageDecoder {

    //List head
    private Node first;
    //List last
    private Node last;
    //The current Node
    private Node currentNode;

    /**
     * This Node class stores an integer list element and
     * a reference to the next node
     */
    private class Node {

        //The integer data
        int value;
        //This is for the reference to the next node
        Node next;
        //The char character from the file
        char character;

        /**
         * Constructor
         *
         * @param val The element to store in the node
         * @param n   The reference to the successor node
         * @param c The reference to the character
         */
        Node(int val, char c, Node n) {
            value = val;
            next = n;
            character = c;
        }
    }

    /**
     * Constructor to initializes the variables that takes no-arguments
     */
    public MessageDecoder(){
        first = null;
        last = null;
        currentNode = null;
    }

    /**
     * The insertInOrder method will insert the number from the file
     * from smallest to largest
     *
     * @param letter The char that is scanned in from the file
     * @param data The number is scanned in from the file
     */
    public void insertInOrderAndChar(char letter, int data){
        //Create an Node object
        Node newNodeNum = new Node(data,letter,first);

        //The reference head of the node that points to the first node
        currentNode = first;
        //There is nothing previously
        last = null;

        //Insert data that is greater than the data
        //that was in the traversed node
        while(currentNode != null && currentNode.value < data){
            //if currentNode is not stored in last, Java will auto delete.
            last = currentNode;
            currentNode = currentNode.next;
        }

        if(last != null) {
            //The last node starts pointing to the new node
            last.next = newNodeNum;
        } else {
            //If the last node is null it will become the first node
            //CHANGE HEAD
            first = newNodeNum;
        }
        //The new node will points to the current node
        // (replacing that current Node value with the new node value)
        //establish new link from head to next.
        newNodeNum.next = currentNode;
    }

    /**
     * This countingDuplicates method will see if the current Node value is
     * equivalent to the head Node value and returns true, otherwise, return
     * false
     *
     * @param head The head node
     * @return True if there are duplicates
     */
    public boolean countingDuplicates(Node head){
        //Counting duplicates number appearances
        int countDup = 0;

        while(head.next != null){
            currentNode = head.next;
            while (currentNode != null && head.value == currentNode.value) {
                countDup++;
                //Set the next current value
                currentNode = currentNode.next;
            }
            //Set the next head value
            head = head.next;
        }
        if(countDup != 0) {
            //There are duplicates
            System.out.println("Error: duplicate total found " + countDup +
                    "\nNo duplicate numbers are allowed.");
            return true;
        }
        return false;
    }

    /**
     * The countingNegative method will return true if there is a negative
     * number, otherwise, return false
     * @param head The head node
     * @return True if there are negative numbers
     */
    public boolean countingNegative(Node head){
        //Counting negative numbers appearance
        int countNeg = 0;

        while(head.next != null &&head.value < 0 ){
            countNeg++;
            head = head.next;
        }
        if(countNeg != 0) {
            //There are duplicates
            System.out.println("Error: negative total found " + countNeg +
                    "\nOnly positive integer values.");
            return true;
        }
        return false;
    }

    /**
     * This scanFile method is responsible for converting a scrambled message
     * file into plain text.
     *
     * @param fileName The name of the file that the user wished to decode
     * @param in The Scanner object
     * @throws FileNotFoundException Signals for an invalid file
     */
    public void scanFile(String fileName, Scanner in) throws FileNotFoundException  {
        //Finding duplicates numbers
        boolean isDuplicates = false;
        //Finding negative numbers
        boolean isNegative = false;
        //The String for reading the line
        String line;

        //Creat the File object
        File file = new File(fileName);
        //Create the Scanner object
        in = new Scanner(file);

        while (in.hasNext()) {
            line = in.nextLine();
            //Creat another scanner object to represent the line
            Scanner lineScanner = new Scanner(line);
            char character = line.charAt(0);
            //If the first character is not a space then consume it
            if (character != ' ') {
                lineScanner.next();
            }
            int number = lineScanner.nextInt();
            insertInOrderAndChar(character, number);

            //Checking for Negatives
            isNegative = countingNegative(first);
            //Checking for Duplicates
            isDuplicates = countingDuplicates(first);

            //Display the malformed message files
            if (isNegative == true || isDuplicates == true) {
                System.out.println("Please fix your file!");
            }
        }
    }

    /**
     * This getPlainTextMessage method will traverses the list
     * and print out all of its elements
     *
     * @return The string object that displayed the messaged
     */
    public String getPlainTextMessage(){
        String str = "";
        currentNode = first;
        while(currentNode != null){
            str += Character.toString(currentNode.character);
            currentNode = currentNode.next;
        }
        return "Decoded: " + str;
    }

}
