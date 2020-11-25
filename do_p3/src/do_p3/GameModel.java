/*
 * Bao Tran Do
 * CPSC 5002, Seattle University
 * This is free and unencumbered software released into the public domain.
 */


package do_p3;
import java.util.Random;
import java.util.ArrayList;

/**
 * The GameModel class have all the game logic to
 * the SillyCardGame.
 *
 * @author Bao Tran Do
 * @version 1.0
 */
public class GameModel {

    //Stack to hold the dealer's cards
    private Stack<Integer> dealCards;
    //Stack to hold the discard's cards
    private Stack<Integer> discard;
    //Queue to hold the player1's hands
    private Queue<Integer> player1;
    //Queue to hold the player2's hands
    private Queue<Integer> player2;


    /**
     * Constructor that takes no arguments
     * Initializes all the field variables
     */
    public GameModel(){
        dealCards = new Stack<>();
        discard = new Stack<>();
        player1 = new Queue<>();
        player2 = new Queue<>();
    }

    /**
     * The setGame method will set the game by
     * building the deck with the shuffling,
     * deal the cards to the players, and discard
     * a card from the deal stack pile.
     */
    public void setGame(){
        //Deck
        cards();
        //Deal the cards
        playerAddCards();
        //Discard a card from the deal stack to start the game
        discard.push(dealCards.pop());
    }

    /**
     * This cards method create the cards that contain the
     * numbers 1-13 and there are 4 copies of each cards
     * in the deck.
     */
    public void cards() {
        //Store all 52 cards into an ArrayList
        ArrayList<Integer> cards = new ArrayList<>();

        //Create 13 cards 4 times
        for (int j = 1; j <= 4; j++) {
            for (int i = 1; i <= 13; i++) {
                cards.add(i);
            }
        }

        //Shuffle the cards
        shuffleDeck(cards);

        //Stack stores the pile of cards that the player is drawing
        for (int i = 0; i < cards.size(); i++){
            dealCards.push(cards.get(i));
        }
    }

    /**
     * The playerAddCards method will add cards to the
     * player hands round robin style.
     */
    public void playerAddCards(){
        for(int i = 1; i <= 7; i++) {
            //Round robin to the players
            player1.enqueue(dealCards.pop());
            player2.enqueue(dealCards.pop());
        }
    }

    /**
     * If the card the player plays is EQUAL in number to the one on
     * the top of the discard stack, the player must then take one card
     * from the deal stack and the player's turn is over.
     *
     * @param playerName The current player's turn
     * @return true if the the player's card number is equal to the
     * top of the discard stack
     */
    public boolean equalsNum(String playerName){
        //Create the reference to the player's object
        Queue<Integer> player = playerObject(playerName);

        //Compare the value do not remove them
        if(player.peek().equals(discard.peek())){
            //Dequeue the current player's card
            discard.push(player.dequeue());
            //Player take one card from the queue
            player.enqueue((dealCards.pop()));
            turnOver();
            return true;
        }
        return false;
    }

    /**
     * The higherNum method returns true if the card the player plays
     * is HIGHER in number than the one on the top of the discard stack,
     * the player's turn is over.
     *
     * @param playerName The current player's turn
     * @return true if the the player's card number is higher than the
     * top of the discard stack
     */
    public boolean higherNum(String playerName){
        //Create the reference to the player's object
        Queue<Integer> player = playerObject(playerName);

        if(player.peek() > discard.peek()){
            //Dequeue the current player's card
            discard.push(player.dequeue());
            turnOver();
            return true;
        }
        return false;
    }

    /**
     * The lowerNum method returns true ff the player's card is LOWER
     * in number than the one on the discard stack, the player must
     * take TWO cards from the deal stack and the player's turn is over.
     *
     * @param playerName The current player's turn
     * @return true if the the player's card number is lower than the
     * top of the discard stack
     */
    public boolean lowerNum(String playerName){
        //Create the reference to the player's object
        Queue<Integer> player = playerObject(playerName);

        if(player.peek() < discard.peek()){
            //Dequeue the current player's card
            discard.push(player.dequeue());
            //Player take 2 cards from the queue
            player.enqueue((dealCards.pop()));
            turnOver();
            player.enqueue((dealCards.pop()));
            turnOver();
           return true;
        }
        return false;
    }

    /**
     * If the deal stack runs out of cards, "turn over" the discard stack
     * and continue the game.
     */
    public void turnOver(){
        if(dealCards.empty()){
            //held on to the card on top of the discard stack
            int variable = discard.pop();
            //Push the remaining cards back to the dealer's hand
            for(int i = 0; i < discard.size(); i++){
                dealCards.push(discard.pop());
            }
            //pushing the top card back
            discard.push(variable);
        }
    }

    /**
     * The getCards method display the player's cards by
     * returning a toString
     *
     * @param player The current player's turn
     * @return a toString of the player's hands.
     */
    public String getCards(String player){
        return playerObject(player).toString();
    }

    /**
     * The getDiscardCard method will peek at the
     * top card on the discard stack and return
     * the value without removing the card
     *
     * @return the value of the top discard card
     */
    public int getDiscardCard(){
        return discard.peek();
    }

    /**
     * The getCurrentPlayerCard method will peek
     * at the top card on the player queue and
     * return the value without removing the card.
     *
     * @param player The current player's turn
     * @return the value of the top card from the queue
     * of the player
     */
    public int getCurrentPlayerCard(String player){
        return playerObject(player).peek();
    }

    /**
     * This emptyHands method will return true if the player
     * doesnt have any more cards left
     *
     * @param playerName The current player's turn
     * @return true if there are no more cards, otherwise, false.
     */
    public boolean emptyHands(String playerName){
        Queue<Integer> player = playerObject(playerName);
        if(player.empty()){
            return true;
        }
        return false;
    }

    /**
     * Returning the reference to the player's object
     *
     * @param player The curent player's turn
     * @return The current player reference object from
     * the queue.
     */
    private Queue<Integer> playerObject(String player){
        if(player.equals("Player1")){
            return player1;
        } else{
            return player2;
        }
    }

    /**
     * Shuffles the cards using the
     * <a href="https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle">
     * Fisher-Yates algorithm</a>
     * @param cards deck to shuffle
     */
    private void shuffleDeck(ArrayList<Integer> cards) {
        Random rand = new Random();
        for (int i = cards.size(); i > 1; i--) {
            int j = rand.nextInt(i);
            int temp = cards.get(i - 1);
            cards.set(i - 1, cards.get(j));
            cards.set(j, temp);
        }
    }
}
