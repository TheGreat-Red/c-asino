#include "../include/blackjack.h"
#include "../include/bankManager.h"
#include <iostream>
#include <cstdlib> //needed for rand()
#include <ctime> //needed for time()
#include <string>
#include <limits> //std::numeric_limits

extern Session session;
extern Bank bank;

const int DECK_SIZE = 52;
std::string deck[DECK_SIZE];
int deckIndex = 0;

//fills the deck with 52 cards and shuffles
void shuffleDeck() {
    std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            deck[index++] = ranks[j];
        }
    }
    //srand is needed to ensure it isn't same digit every time
    std::srand(static_cast<unsigned>(std::time(0))); //makes sure the digit starts at a different place each time.
    for (int i = 0; i < DECK_SIZE; ++i) { 
        int r = std::rand() % DECK_SIZE;
        std::swap(deck[i], deck[r]);
    }
    deckIndex = 0;
}

//draws card by simply returning the next shuffled card
std::string drawCard() {
    return deck[deckIndex++];
}

//gets the value for the face cards
int getCardValue(const std::string& card) {
    if (card == "J" || card == "Q" || card == "K") return 10;
    if (card == "A") return 11;
    return std::stoi(card);
}

//calculates total of hand
int getTotal(std::string hand[], int count) {
    int total = 0, aceCount = 0;
    for (int i = 0; i < count; ++i) {
        total += getCardValue(hand[i]);
        if (hand[i] == "A") aceCount++;
    }
    while (total > 21 && aceCount > 0) {
        total -= 10;
        aceCount--;
    }
    return total;
}
//Shows the hand
void showHand(std::string hand[], int count, const std::string& who) {
    std::cout << who << "'s hand: ";
    for (int i = 0; i < count; ++i) std::cout << hand[i] << " ";
    std::cout << "(Total: " << getTotal(hand, count) << ")\n";
}


//MAIN GAME LOGIC BELOW

void blackjack::play() { //calls game
    shuffleDeck(); //shuffles deck
    std::string playerHand[10], dealerHand[10]; //'max' number of cards
    int playerCount = 0, dealerCount = 0; //starts with 0 cards total 

    std::string input;
    double betAmount = 0;

    // Get the player's bet
    while (true) {
        std::cout << "\nYour current balance: $" << bank.getBalance() << "\n";
        std::cout << "Enter a bet amount between 100 and 1000: ";
    
        std::getline(std::cin, input);  // always read full line
    
        try {
            // Remove any leading/trailing whitespace (optional safety)
            input.erase(0, input.find_first_not_of(" \t\r\n"));
            input.erase(input.find_last_not_of(" \t\r\n") + 1);
    
            betAmount = std::stod(input);
    
            if (betAmount < 100 || betAmount > 1000) {
                std::cout << "Bet must be between 100 and 1000.\n";
                continue;
            }
    
            if (bank.getBalance() < betAmount) {
                std::cout << "Insufficient funds.\n";
                continue;
            }
    
            bank.subtractFunds(betAmount);
            break;
    
        } catch (...) {
            std::cout << "Invalid input.\n";
            std::cin.clear(); // just in case
            // only flush if getline failed (rare, but safe to include)
        }
    }
    
    
    


    //Initial cards are dealt here, 2 player 2 dealer
    playerHand[playerCount++] = drawCard();
    dealerHand[dealerCount++] = drawCard();
    playerHand[playerCount++] = drawCard();
    dealerHand[dealerCount++] = drawCard();

    showHand(playerHand, playerCount, "Player");//reveals all player cards
    std::cout << "Dealer shows: " << dealerHand[0] << " [UNKNOWN CARD]\n";//keeps 2nd card hidden

    while (true) {
        int total = getTotal(playerHand, playerCount);
        if (total > 21) { 
            std::cout << "Over 21, you busted!\n";
            return;
        }
        std::cout << "Hit or Stand? (h/s): ";
        char choice;
        std::cin >> choice;
        if (choice == 'h') {
            playerHand[playerCount++] = drawCard();
            showHand(playerHand, playerCount, "Player");
        } else {
            break;
        }
    }
    std::cin.ignore();

    std::cout << "Dealer reveals hand:\n";
    showHand(dealerHand, dealerCount, "Dealer"); //reveals entire hand now
    while (getTotal(dealerHand, dealerCount) < 17) { //hardcoded value to determine when the dealer will bet or not
        dealerHand[dealerCount++] = drawCard();
        showHand(dealerHand, dealerCount, "Dealer");
    }

    //uses the getTotal function and stores to individual variables
    int playerTotal = getTotal(playerHand, playerCount);
    int dealerTotal = getTotal(dealerHand, dealerCount);

    std::cout << "Final Scores - Player: " << playerTotal << ", Dealer: " << dealerTotal << "\n";


    //decide who wins using the variable I created above
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        std::cout << "You win!\n";
        bank.addFunds(betAmount * 2);
        session.wins++;
    } else if (playerTotal < dealerTotal) {
        std::cout << "You lose.\n";
        session.losses++;
    } else {
        std::cout << "It's a tie! Your bet is returned.\n";
        bank.addFunds(betAmount);
    }
}
