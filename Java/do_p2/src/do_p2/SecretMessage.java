/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p2;
import java.util.Scanner;
import java.io.File;
import java.io.IOException;

/**
 * The SecretMessage class will display the decoded message from the user's
 * input file.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class SecretMessage {

    /**
     * Main application method that called other method for the standard output
     * @param args Reads in the inputs
     * @throws IOException Check for exceptions
     */
    public static void main(String[] args) throws IOException{
        //Display the welcoming message
        welcome();

        //Create a Scanner object
        Scanner in = new Scanner(System.in);

        //Unravel the message and prompt the user to go again
        do {
            unRavelMessage(in);
        }while(again(in));

        //Display the goodbye message
        goodbye();

        //Closed the scanner object
        in.close();
    }

    /**
     * This unRavelMessage method will unravel the message from the file
     * @param in The Scanner object
     * @throws IOException Check for exceptions
     */
    public static void unRavelMessage(Scanner in) throws IOException{
        //Check whether or not the file exist
        boolean exist = false;
        //A string for fileName
        String fileName;

        do {
            //Ask the user to enter the file name
            System.out.print("Enter secret file name: ");
            fileName = in.nextLine();

            //Check if the file exist
            exist = isValidFile(fileName);
        } while(!exist);

        //Create the MessageDecoder object
        MessageDecoder messDeco = new MessageDecoder();
        //Open(Scan) the file
        messDeco.scanFile(fileName,in);
        //Print out the decoded
        System.out.println(messDeco.getPlainTextMessage());

    }


    /**
     * Checks to see that the user-specified file name refers to a valid
     * file on the disk and not a directory. Displays an error message to the
     * user if that is not the case.
     * @param fname file name string to check
     * @return true if file exists on disk and is not a directory
     */
    private static boolean isValidFile(String fname) {
        File path = new File(fname);
        boolean isValid = path.exists() && !path.isDirectory();
        if (!isValid) {
            // TODO: Display a proper error message
            System.out.println("This file does not exist!");
        }
        return isValid;
    }

    /**
     * This again method ask the user if they want to enter another file
     * name to decode
     * @param in Pass in the Scanner object
     * @return Let the user to re-enter the file again if they desire to
     */
    public static boolean again(Scanner in){
        String user;
        boolean again = false;

        System.out.println();
        //Ask the user to play the game again
        System.out.print("Would you like to try again? Enter yes or no: ");
        user = in.nextLine();

        if(user.equalsIgnoreCase("yes")) {
            System.out.println("---------------------------------------------");
            again = true;
        }
        return again;
    }

    /**
     * The weclome method display the Welcoming message
     */
    public static void welcome(){
        System.out.println("Welcome!");
        System.out.println("This program reads an encoded message from a " +
                "\nfile supplied by the user and displays the contents of " +
                "\nthe message before it was encoded.");
        System.out.println();
    }

    /**
     *The goodbye method display the goodbye message
     */
    public static void goodbye(){
        System.out.println("Thank you for using the message decoder.");
        System.out.println("Goodbye!");
    }
}
