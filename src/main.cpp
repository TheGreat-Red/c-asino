#include <iostream>
#include <string>

#include "../include/authManager.h"
#include "../include/casinoUi.h"



int main()
{

    while (true) {
        if (!AuthManager::authMenu()) return 0;
        std::cout << "Login failed. Please try again.\n";
    }

    displayMainMenu(); 

    return 0;
}