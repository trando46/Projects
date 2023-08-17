/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */

package do_p1;

/**
 * This TicTacToe class simulates the Tic-Tac-Toe game between
 * two players. One player places the X pieces and the other
 * places the O pieces. The basic game board is a grid of 9
 * spaces in a 3x3 arrangement(although the game should be
 * flexible enough to handle a 5x5, 7x7 or any other size in
 * the future). When one player covers an entire row, column,
 * or diagonal, that player wins the game.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class TicTacToe {

    //A 2D array game board for TicTacToe
    private String[][] gameBoard;
    //The size variable represent the row or the column
    private int SIZE;
    //This value represent the player "X"
    private final String PLAYER_X;
    //This value represent the player "O"
    private final String PLAYER_O;
    //The master strings of "X" and "O" to determine wins
    private String masterStrX, masterStrO;

    /**
     * Constructor that initializes all variables and pass
     * in the size of the game board
     *
     * @param rowXCol The size of the game board
     */
    public TicTacToe(int rowXCol) {
        SIZE = rowXCol;
        PLAYER_X = "X";
        PLAYER_O = "O";
        gameBoard = new String[SIZE][SIZE];
        masterStrX = masterStr(PLAYER_X);
        masterStrO = masterStr(PLAYER_O);

        //fill the board with spaces
        fillBoardSpaces(SIZE);
    }

    /**
     * The getSize function get the value of the size of the board.
     * The size is representing sizeXsize grid of the board.
     *
     * @return The size of the board: sizeXsize grid of the board.
     */
    public int getSize() {
        return SIZE;
    }

    /**
     * This fillBoardSpaces will fill the spaces in the
     * board so that it does not display "null"
     *
     * @param spaces Fill in the spaces of the board
     */
    public void fillBoardSpaces(int spaces) {
        //Fill the board with spaces
        for (int row = 0; row < spaces; row++)
            for (int col = 0; col < spaces; col++)
                gameBoard[row][col] = " ";
    }

    /**
     * This masterStr method is the pattern of the
     * player's win
     * @param player The player "X" or player "O"
     * @return Player win pattern.
     */
    public String masterStr(String player) {
        //Accumulator
        String user = "";
        for(int i = 0; i < SIZE; i++) {
            user += player;
        }
        return user;
    }

    /**
     * This setLocation method will set the location that the
     * player enter.
     *
     * @param player The player "X" or player "O"
     * @param row The index of the row
     * @param col The column of the row
     */
    public void setLocation(String player, int row, int col) {
        if (gameBoard[row][col].equals(" ")){
            gameBoard[row][col] = player;
        }
    }

    /**
     * This toString method creates the representation of the board
     *
     * @return String representation
     */
    public String toString() {

        //Header of the columns labeling
        String headerCol = "  ";
        //Header of the row labeling
        String headerRow = "";
        //Return an empty string so that it doesnt affect the board
        String empty = "";

        //Print out the header
        for(int i = 0; i < SIZE; i++) {
            headerCol += "    " + (i);
        }
        System.out.println(headerCol);

        //Print out the board
        for(int i = 0; i < SIZE; i++){
            headerRow = (i) + " ";
            for(int j = 0; j < SIZE; j++) {
                headerRow += " |  " + gameBoard[i][j];
            }
            System.out.println(headerRow);
            for(int k = 0; k < (SIZE -1) * 8 ; k++) {
                System.out.print("-");
            }
            System.out.println();
        }
        return empty;
    }

    /**
     * This checkRow method return to true if there are
     * rows for any winning and return false if there is no winning
     *
     * @return True if there is a win in a row.
     */
    public boolean checkRow(){
        //Accumulator
        String count = "";

        for(int row = 0; row < gameBoard.length; row++) {
            //Rest the count
            count = "";
            for(int col = 0; col < gameBoard[row].length; col++){
                count += gameBoard[row][col];
            }
            if(count.equals(masterStrX) || count.equals(masterStrO)) {
                return true;
            }
        }
        return false;
    }

    /**
     * This checkDiag method returns true if there are diagonal's wins. Else
     * will return false if no diagonal's wins are found.
     *
     * @return True if there is diagonal win.
     */
    public boolean checkDiag(){
        //Accumulator
        String principal = "", secondary = "";

        //Diagonals
        for(int i = 0; i < SIZE; i++) {
            //row-column condition: row = column
            principal += gameBoard[i][i];
            //row-column condition: row = numberOfRows - columns - 1
            secondary += gameBoard[i][SIZE - i - 1];
            if(principal.equals(masterStrX) || principal.equals(masterStrO) ||
                    secondary.equals(masterStrX) || secondary.equals(masterStrO)) {
                return true;
            }
        }
        return false;
    }

    /**
     * This checkCol method returns true if there are column's wins. Else
     * will return false if no column's wins are found.
     *
     * @return True if there is a column win.
     */
    public boolean checkCol(){
        //Accumulator
        String count = "";

        for(int col = 0; col < gameBoard[0].length; col++) {
            //Reset the accumulator
            count = "";
            for(int row = 0; row < gameBoard.length; row++) {
                count += gameBoard[row][col];
            }
            if(count.equals(masterStrX) || count.equals(masterStrO)) {
                return true;
            }
        }
        return false;
    }

    /**
     * This win method will filter through the patterns for winning.
     *
     * @param player The player "X" or player "O"
     * @return The pattern of the winner.
     */
    public boolean win(String player){
        return (checkRow() || checkCol() ||checkDiag());
    }

    /**
     * This displayWinner method will display who is the winner
     * @param player The player "X" or player "O"
     * @return True if there is a winner
     */
    public boolean displayWinner(String player){
        if(win(player)) {
            System.out.println();
            System.out.println(player + " is the winner!");
            return true;
        }
        return false;
    }

    /**
     * This checkBoardFull method check whether or not the board is full
     *
     * @return True if the board is full.
     */
    public boolean checkBoardFull(){
        //Empty string with a space
        String empty = " ";

        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                if (gameBoard[row][col].equals(empty)) {
                    // a move still exists - board is not full
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * This isValid method will return false if it is not a valid spot
     * or the user enter the number out of bound.
     *
     * @param row The index of the row
     * @param col The index of the column
     * @return False if the spot is not valid or it is out of bound.
     */
    public boolean isValid(int row, int col) {
        //Empty string with a space
        String empty = " ";

        if(row > SIZE || col > SIZE || row < 0 || col < 0) {
            System.out.println("Space is out of bound! Try again!");
            return false;
        }
        if(!gameBoard[row][col].equals(empty)) {
            System.out.println("Space is occupied. Enter a new space!");
            return false;
        }
        return true;
    }

    /**
     * This displayScoreBoard method display the score board
     * of winning.
     *
     * @param countX The win count for player X
     * @param countO The win count for player O
     * @param countTie The tie count between two players
     */
    public void displayScoreBoard( int countX, int countO, int countTie){
        System.out.println("The Score Board: ");
        System.out.println("----------------");
        System.out.println("X has won " + countX + " games.");
        System.out.println("O has won " + countO + " games.");
        System.out.println("There has been " + countTie + " tie games.");
    }
}






