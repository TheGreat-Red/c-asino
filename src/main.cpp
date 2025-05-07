#include <iostream>
#include <string>

#include "../include/AuthManager.h"
#include "../include/casinoUI.h"



int main()
{

    while (true) {
        if (!AuthManager::authMenu()) return 0;
        std::cout << "Login failed. Please try again.\n";
    }

    displayMainMenu(); 

    return 0;
}