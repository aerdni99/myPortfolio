/*

    Card class file

*/

/*

    Suit is a value from 1-4. each number corresponding to Spades, Hearts, Diamonds, and Clubs respectively
    Rank is a value from 2-14. Values 2-10 represent ranks 2-10 as one would expect. 
        Ranks 11, 12, 13, and 14 represent Jack, Queen, King, and Ace respectively.
        This way, ranks can be accurately compared with normal integer comparison statements.

*/
public class Card {
    
    int suit;
    int rank;
    
    // Default Ctor not used in this program
    public Card() {
        suit = 0;
        rank = 0;
    }
    
    // Card initialized from 2 values suit and rank
    public Card(int s, int r) {
        suit = s;
        rank = r;
    }
    
    // Set and Get methods defined, but set is never used. Collections.swap() takes care of swapping cards.
    public void setSuit(int s) {
        suit = s;
    }
    
    public void setRank(int r) {
        rank = r;
    }
    
    public int getSuit() {
        return suit;
    }
    
    public int getRank() {
        return rank;
    }
}
