#include <iostream>
#include <random>
#include <string>

#include "../include/DiceDuel.h"
#include "../include/AuthManager.h"

void DiceDuel::start()
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
        std::cout << "1. Start\n2. Back\n";

        getline(std::cin, input);
        try
        {
            if (stoi(input) == 1)
            {
                randomLogic(); 
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
    
    saveUsersToCSV(AuthManager::users, "users.csv");
}
    

void DiceDuel::randomLogic()
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 6);

    while (true)
    {
        std::string wagerStr;
        int wager;

        while (true)
        {
            std::cout << "Enter wager: \n";
            getline(std::cin, wagerStr);

            try
            {
                wager = stoi(wagerStr);
                if (wager <= 0) 
                    throw;
            }
            catch(const std::exception& e)
            {
                std::cout<< "Invalid input. Please enter a positive number";
                continue;
            }
            break;
        }

        int dealerRoll = dist(gen);
        int playerRoll = dist(gen);

        std::cout << "Dealer: " << dealerRoll << "\n";
        std::cout << "You: " << playerRoll << "\n";

        if (dealerRoll > playerRoll)
        {
            std::cout << "Dealer wins!\n";
            AuthManager::currentUser.balance -= wager;
        }
        else if (playerRoll > dealerRoll)
        {
            std::cout << "You win!\n";
            AuthManager::currentUser.balance += wager;
        }
        else
        {
            std::cout << "It's a tie!\n";
        }

        // saveUsersToCSV()

        while (true)
        {
            std::string input;
            std::cout << "Would you like to duel again? y/n\n";
            getline(std::cin, input);
            if (input == "y")
            {
                break; 
            }
            else
            {
                return;
            }
        }
    }
}
