#include <iostream>
#include <string>

#include "../include/mainMenu.h"
#include "../include/gameManager.h"
#include "../include/bankManager.h"

MainMenu::MainMenu(Session& s) : session(s) {}



// Method/function definition outside the class
void MainMenu::displayMenu()
{
  while (true)
  {
    std::cout<< session.username << "\n";
    std::cout<<R"(
    Welcome to the C++asino!
    What would you like to do?
    1. Games
    2. Account
    3. Exit
    )";

    std::string input; 
    getline(std::cin, input);
  
    try
    {
      if (stoi(input) == 1)
      {
        GameManager game(session);
        game.listGames();

      }

      else if  (stoi(input) == 2)
      {
        Bank bank(session);
        bank.bankScreen();

      }

      else if  (stoi(input) == 3)
      {
        return;
      }

      else
      {
        std::cout<< "Not a valid option";
      }
  
    }
    catch(...)
    {
      std::cout<< "Please enter a valid number";
    }
      

  }
}