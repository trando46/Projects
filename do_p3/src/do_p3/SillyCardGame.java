/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p3;

import java.util.Scanner;

/**
 * The SillyCardGame class will have all of the output to the
 * screen and reading from the keyboard is to be done here. This
 * class has a main method that will start the game. Only
 * unexpected error messages are allowed to be displayed on the
 * screen from other classes.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class SillyCardGame {

    /**
     * Main application method that called other method
     * for the standard output
     *
     * @param args Reads in the inputs
     */
    public static void main(String[] args){

        //Create the Scanner Object
        Scanner in = new Scanner(System.in);

        //Display the welcome message
        welcome();

        //Simulates the game
        do {
            game();
        }while(again(in));

        //Display the goodbye messsage
        goodbye();

        //Closed the Scanner object
        in.close();
    }

    /**
     * This game method start the game play of the
     * SillyCardGAme
     */
    public static void game(){
        //Create the GameModel object
        GameModel fun = new GameModel();

        //First player is player1
        String player = "Player1";

        //Game is over
        boolean gameOver = false;

        //set the game
        fun.setGame();

        while(!gameOver){
            System.out.println(player +"'s turn,cards: " );
            System.out.println(fun.getCards(player));
            System.out.println("Discard pile card: " + fun.getDiscardCard());
            System.out.println("Your current card: "
                    + fun.getCurrentPlayerCard(player));

            //Checking the relationship between the player peek(top) card
            //and the discard peek(top) card
            if(fun.equalsNum(player)){
                System.out.println("Your card is EQUAL, pick up 1 card. ");
            } else if(fun.higherNum(player)){
                System.out.println("Your card is HIGHER, turn is over.");
            } else if(fun.lowerNum(player)){
                System.out.println("Your card is LOWER, pick up 2 cards.");
            }

            //Check if the player's hands is empty
            if(fun.emptyHands(player)){
                System.out.println("!!!GAME OVER!!!");
                System.out.println(player + " won the game!");
                //End the game
                gameOver = true;
            }

            if(!gameOver) {
                System.out.println();
                System.out.println("-------------------------------------");
                System.out.println();

                //Switch between players
                if(player.equals("Player1")){
                    player = "Player2";
                } else {
                    player = "Player1";
                }
            }
        }
    }

    /**
     * This again method ask the user if they want to play again
     * @param in Pass in the Scanner object
     * @return Let the user to re-enter the file again if they desire to
     */
    public static boolean again(Scanner in){
        String user;
        boolean again = false;

        System.out.println();
        //Ask the user to play the game again
        System.out.print("Play again? Enter yes or no: ");
        user = in.nextLine();

        if(user.equalsIgnoreCase("yes")) {
            System.out.println("---------------------------------------------");
            again = true;
        }
        return again;
    }

    /**
     * The welcome method display the Welcoming message
     */
    public static void welcome(){
        System.out.println("Welcome!");
        System.out.println("The game company, Silly Little Games, has " +
                "\ncome up with a new card game. It is a two person game. " +
                "\nThe game uses a special set of cards that contain the " +
                "numbers 1 " +
                "\nto 13 and there are four copies of each card in the deck. " +
                "\nThe first person to play all the cards in their hand wins!");
        System.out.println();
    }

    /**
     *The goodbye method display the goodbye message
     */
    public static void goodbye(){
        System.out.println("Thank you for playing this game!");
        System.out.println("Goodbye!");
    }
}
