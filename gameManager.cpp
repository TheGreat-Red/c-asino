#include <iostream>
#include <string>

#include "../include/gameManager.h"
#include "../include/diceDuel.h"
#include "../include/mainMenu.h"

GameManager::GameManager(Session& s) : session(s) {}


void GameManager::listGames()
{


   
    while (true)
    {
        std::string input;

        std::cout<< session.username << "\n";
        //could create a variable if wanted to dynamically increase count size
        std::cout<< R"(
        Available Games:
        1. Dice Duel
        2. Game Two (Ends Program)
        3. Game Three (Ends Program)
        4. Back)"; std::cout<< std::endl;
        getline(std::cin, input);

        try
        {
            if (stoi(input) == 1)
            {
                diceDuel duel(session);
                duel.start();
            }
            else if (stoi(input) == 2)
            {
                std::cout<< "gameTwoclass method\n";
                break;
    
            }
            else if (stoi(input) == 3)
            {
                std::cout<< "gameThreeclass method\n";
                break;
            }
            else if (stoi(input) == 4)
            {
                break;
            }
            else
            {
                std::cout<< "invalid choice";
            }
        }
        catch(...)
        {
            std::cerr << "Please enter a valid number";
        }
        
        
    }
}