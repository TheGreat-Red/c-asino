#include <iostream>
#include <string>

#include "../include/authManager.h"
#include "../include/session.h"
#include "../include/bankManager.h"
#include "../include/casinoUi.h"

Session session;
AuthManager auth(session);
Bank bank(session);

int main() {
    while (true) {
        if (!auth.authMenu()) return 0;
        if (!session.username.empty()) break;
        std::cout << "Login failed. Please try again.\n";
    }


    displayMainMenu(session); 

    return 0;
}