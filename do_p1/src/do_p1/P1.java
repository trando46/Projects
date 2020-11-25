/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p1;
import java.util.Scanner;

/**
 * This P1 class create the TicTacToe game between two players. One player
 * is X and the other player is O. This game will check if the player win base
 * on rows, columns, or diagonals and display the winner and how many wins.
 * This game also checked whether or not it is a tie and will display that there
 * is a tie. The players can play this game as many times as they want unless
 * they say no.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class P1 {

    /**
     * Main application method
     *
     * @param args Get keyboard inputs
     */
    public static void main(String[] args) {
        //Create a Scanner object
        Scanner in = new Scanner(System.in);
        //Create the TicTacToe object
        TicTacToe game = new TicTacToe(3);

        //Display the welcoming message
        welcome();

        //Game
        do {
            play(in,game);

        } while(again(in));

        //Display the goodbye message
        goodbye();

        //close the scanner
        in.close();
    }

    /**
     * This welcome method displays the welcoming message
     */
    public static void welcome() {
        System.out.println("Welcome to TicTacToe!");
        System.out.println("This is a game between you and your friend." +
                "\nThe first player is X and the second player is O." +
                "\nThe player that win must fill up one row or column or " +
                "\ndiagonal. Otherwise, the game is a tie!");
    }

    /**
     * This goodbye method displays the exiting message
     */
    public static void goodbye() {
        System.out.println("\n" + "Thanks for playing!" + "\nGoodbye!");
    }

    /**
     * This play method ask the user if they want to
     * play the game of TicTacToe
     *
     * @param in Pass in the Scanner object
     * @param game Pass in the TicTacToe object
     */
    public static void play(Scanner in, TicTacToe game){
        //First player is X
        String player = "X";
        boolean gameOver = false;
        //Finding winner
        boolean winner = false;
        //Finding ties
        boolean tie = false;
        //The row's value
        int row;
        //The column's value
        int column;

        //Reset the board
        game.fillBoardSpaces(game.getSize());

        //Accumulator for the wins
        int countX = 0, countO = 0, countTie = 0;

        while(!gameOver) {

            //Prompt the user to enter the location
            //verify that location is valid
            do {
                System.out.print(game.toString());

                //Get row value
                System.out.println(player + ", it is your turn.");
                System.out.print("Which row? : ");
                row = in.nextInt();
                //Get columns value
                System.out.print("Which columns? : ");
                column = in.nextInt();

            } while(!game.isValid(row, column));

            //Set the location
            game.setLocation(player, row, column);

            //Check for winners
            winner = game.displayWinner(player);
            if (winner == true) {
                if (player.equals("X")) {
                    //System.out.println();
                    System.out.print(game.toString());
                    countX++;
                } else if (player.equals("O")) {
                    //System.out.println();
                    System.out.print(game.toString());
                    countO++;
                }
                //Terminate the game
                gameOver = winner;
            }

            //Check if the game board is full
            tie = game.checkBoardFull();
            if (tie == true) {
                System.out.println();
                System.out.println("No winner - it is a tie!");
                System.out.print(game.toString());
                countTie++;
                //Terminate the game
                gameOver = tie;
            }

            //Switch between players
            if (player.equals("X"))
                player = "O";
            else
                player = "X";
        }
        //Display the score board
        game.displayScoreBoard(countX,countO,countTie);
    }

    /**
     * This again method ask the user if they want to
     * play the game again.
     *
     * @param in Pass in the Scanner object
     * @return Let's the user to play again if they desire to
     */
    public static boolean again(Scanner in){
        String user;
        boolean again = false;

        //Ask the user to play the game again
        System.out.print("Play again? Enter yes or no: ");
        user = in.nextLine();
        user = in.nextLine();

        if(user.equalsIgnoreCase("yes")) {
            System.out.println();
            again = true;
        }
        return again;
    }

}
