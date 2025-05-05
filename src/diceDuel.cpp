#include <iostream>
#include <random>
#include <string>

#include "../include/diceDuel.h"
#include "../include/gameManager.h"
#include "../include/bankManager.h"

extern Session session;
extern Bank bank;

diceDuel::diceDuel(Session& s) : session(s) {}


void diceDuel::start()
{
    

    std::cout<< R"(
        Welcome to Dice Duel!!!
        In this game, you'll face off against the house in a simple battle of luck.
        Here's how it works:
        You and the house will each roll a 6-sided die.
        Whoever rolls the higher number wins the round.
        If you both roll the same number, it's a draw.
        You can choose to duel again or return to the game menu.
        Think you can beat the house? Let's find out.

        )";


    while (true)
    {
        std::string input;
        std::cout<< R"(
        1. Start
        2. Back)"; std::cout<< std::endl;
        getline(std::cin, input);
        try
        {
            if (stoi(input) == 1)
            {
                randomLogic(bank); 
            }

        
            else if (stoi(input) == 2)
            {
                break;
            }
            else
            {
                std::cout<< "Not a valid choice";
            }
        }
        catch(...)
        {
            std::cout<< "Please enter a valid number";
        }
        
        
    }

}
    

void diceDuel::randomLogic(Bank& bank)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 6);

    while (true)
    {
        if (!bank.bet())
        {
            std::cout << "Invalid wager. Returning to menu.\n";
            return;
        }

        int dealerRoll = dist(gen);
        int playerRoll = dist(gen);

        std::cout << "Dealer: " << dealerRoll << "\n";
        std::cout << "You: " << playerRoll << "\n";

        if (dealerRoll > playerRoll)
        {
            std::cout << "Dealer wins!\n";
            bank.lose();
        }
        else if (playerRoll > dealerRoll)
        {
            std::cout << "You win!\n";
            bank.win();
        }
        else
        {
            std::cout << "It's a tie!\n";
        }

        while (true)
        {
            std::string input;
            std::cout << "Would you like to duel again? y/n\n";
            getline(std::cin, input);
            if (input == "y")
            {
                break; 
            }
            else if (input == "n")
            {
                return; 
            }
            else
            {
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
            }
        }
    }
}
