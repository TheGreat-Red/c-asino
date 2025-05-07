#include <cstdlib>
#include <ctime>

#include "../include/session.h"
#include "../include/slotMachine.h"
#include "../include/bankManager.h"

extern Bank bank;
extern Session session;

slotMachine::slotMachine() {}

const char symbols[] = {'@', '#', '%', '?', '&'};


void slotMachine::start() {
    srand(static_cast<unsigned int>(time(0))); //Gets time to esnure comepletely random numbers
    std::string input;
    double betAmount;


    std::cout << "Welcome to the Slot Machine, " << session.username << "!\n";

    while (true) {
        std::cout << "\nYour current balance: " << bank.getBalance() << "\n";
        std::cout << "Press 'Enter' to play or type '1' to exit: ";
        std::getline(std::cin, input);

        if (input == "1") {
            std::cout << "Thanks for playing!\n";
            break;
        }

        if (input.empty()) { //If user hits enter
            std::cout << "Enter a bet amount between 100 and 1000: ";
            std::getline(std::cin, input);

            try {
                betAmount = std::stod(input);  

                // Validate the bet amount
                if (betAmount < 100 || betAmount > 1000) {
                    std::cout << "Bet amount must be between 100 and 1000.\n";
                    continue;  // Ask again for the bet if it's invalid
                }

                // Check if the user has enough balance to place the bet
                if (bank.getBalance() < betAmount) {
                    std::cout << "You don't have enough funds to place that bet.\n";
                    continue;  // Ask again if balance is insufficient
                }

                bank.subtractFunds(betAmount);

                char slot1 = symbols[rand() % 5];    //randomizes the results using the built in rand() function
                char slot2 = symbols[rand() % 5];
                char slot3 = symbols[rand() % 5];

                std::cout << "|| " << slot1 << " | " << slot2 << " | " << slot3 << " ||\n";

                // Check if the user wins
                if (slot1 == slot2 && slot2 == slot3) {
                    double winnings = betAmount * 10; //JACKPOT
                    bank.addFunds(winnings);
                    std::cout << "JACKPOT! You matched all three symbols!\n";
                    std::cout << "You won: " << winnings << "\n";
                    session.wins++;
                } else if (slot1 == slot2 || slot2 == slot3 || slot1 == slot3) {
                    // Win with two matching symbols
                    double winnings = betAmount * 2; //If 2 matching it doubles your bet
                    bank.addFunds(winnings);
                    std::cout << "Nice! You got two matching symbols!\n";
                    std::cout << "You won: " << winnings << "\n";
                    session.wins++;
                } else {
                    std::cout << "No match, better luck next time!\n";
                    session.losses++;
                }

                // Show the updated balance
                std::cout << "Your current balance: " << bank.getBalance() << "\n";
                
            } catch (std::exception& e) {
                std::cout << "Invalid input. Please enter a valid number.\n";   //Ensures integer value is entered
                continue;
            }
        } else {
            std::cout << "Invalid input. Please press 'Enter' to play or type '1' to exit.\n";
            continue;
        }
    }
}
