/*

    driver code for deck manipulation tasks

*/

/*

    A change I would make to this program that was not specified in the task is to 
    implement the deck as a class with a private member of type List<Card>.
    Then all the static methods in this file could be methods of the deck class

*/

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class App {
    public static void main(String args[]) {

        List<Card> deck = new ArrayList<Card> ();
        fillDeck(deck);
        printDeckSize(deck);

        System.out.println("Shuffled Deck: ");
        shuffleDeck(deck);
        printDeck(deck);

        System.out.println("\nSorted by rank: ");
        rankSort(deck);
        printDeck(deck);

        System.out.println("\nSorted by suit and rank: ");
        suitAndRankSort(deck);
        printDeck(deck);

    }
    
    // Takes a list, clears it, and populates it with the 52 basic playing cards
    public static void fillDeck(List<Card> deck) {
        deck.clear();
        for (int i = 1; i < 5; i++) {
            for (int j = 1; j < 14; j++) {
                Card topCard = new Card(i, (j + 1) % 15);   // i and the j statement evaluate to proper rank and suit fields for each card
                deck.add(topCard);
            }
        }
    }
    
    // Takes the deck and outputs to console its size
    public static void printDeckSize(List<Card> deck) {
        System.out.println(deck.size() + " cards in a deck.\n");
    }
    
    // Decodes the integer values of a card object and outputs the card to console
    public static void readCard(Card topCard) {
        String card = "";
        int rank = topCard.getRank();
        int suit = topCard.getSuit();
        switch (rank) {
          case 2:
            card += "TWO of ";
            break;
          case 3:
            card += "THREE of ";
            break;
          case 4:
            card += "FOUR of ";
            break;
          case 5:
            card += "FIVE of ";
            break;
          case 6:
            card += "SIX of ";
            break;
          case 7:
            card += "SEVEN of ";
            break;
          case 8:
            card += "EIGHT of ";
            break;
          case 9:
            card += "NINE of ";
            break;
          case 10:
            card += "TEN of ";
            break;
          case 11:
            card += "JACK of ";
            break;
          case 12:
            card += "QUEEN of ";
            break;
          case 13:
            card += "KING of ";
            break;
          case 14:
            card += "ACE of ";
            break;
          default:
            break;
          }
        switch (suit) {
          case 1:
            card += "SPADES";
            break;
          case 2:
            card += "HEARTS";
            break;
          case 3:
            card += "DIAMONDS";
            break;
          case 4:
            card += "CLUBS";
            break;
          default:
            break;
          }
         System.out.println(card);
    }
    
    // Bubble sort of a deck by rank field comparisons
    public static void rankSort(List<Card> deck) {
        for (int i = 0; i < 52; i++){
            for (int j = 0; j < 52; j++) {
                if (deck.get(i).getRank() < deck.get(j).getRank()) {
                    Collections.swap(deck, i, j);
                }
            }
        }
    }
    
    // Repeated calls to readCard() output all cards to console in order
    public static void printDeck(List<Card> deck) {
        for (int i = 0; i < 52; i++) {
            Card topCard = deck.get(i);
            readCard(topCard);
        }
    }
    
    // Collections.shuffle() randomizes the order of our Deck list
    public static void shuffleDeck(List<Card> deck) {
        Collections.shuffle(deck);
    }

    // a call first to rankSort() then 4 calls to sortOneRank will order the whole deck
    public static void suitAndRankSort(List<Card> deck) {
        rankSort(deck);

        int thisSuit = 1;
        int offset = 0;
        sortOneRank(deck, thisSuit, offset);
        thisSuit += 1;                          // Suit sort always has the same order since the suit we're looking for ranges 1-4 always
        offset += 13;                           // Index offset is incremented by 13 every call to account for 13 cards per set
        sortOneRank(deck, thisSuit, offset);
        thisSuit += 1;
        offset += 13;
        sortOneRank(deck, thisSuit, offset);
        thisSuit += 1;
        offset += 13;
        sortOneRank(deck, thisSuit, offset);

        
    }

    // searches the deck for each rank under one suit and places it in the proper index determined by rank and offset variables
    public static void sortOneRank(List<Card> deck, int thisSuit, int offset) {
        int thisRank = 2;
        while (thisRank < 15) {     // Keep traversing the deck until all cards are in place
            for (int i = 0 + offset; i < 52; i++) {
                if (deck.get(i).getRank() == thisRank && deck.get(i).getSuit() == thisSuit) {     // Check for matching suit and rank
                    Collections.swap(deck, i, thisRank - 2 + offset);
                    thisRank += 1;
                }
            }
        }
    }
}
