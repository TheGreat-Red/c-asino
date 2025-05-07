#include <iostream>
#include <string>

#include "../include/authManager.h"
#include "../include/session.h"
#include "../include/bankManager.h"
#include "../include/casinoUi.h"
#include <windows.h>
Session session;
AuthManager auth(session);
Bank bank(session);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        if (!auth.authMenu()) return 0;
        if (!session.username.empty()) break;
        std::cout << "Login failed. Please try again.\n";
    }


    displayMainMenu(session); 

    return 0;
}