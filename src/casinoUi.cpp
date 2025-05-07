#include <iostream>
#include <limits>
#include <iomanip>

#include "../include/casinoUi.h"
#include "../include/blackjack.h"
#include "../include/diceDuel.h"
#include "../include/slotMachine.h"
#include "../include/bankManager.h"
#include "../include/csvHelper.h"

using namespace std;

extern Session session;

//Input Validation
// Ensures input is a number between min and max
int getValidatedInput(int min, int max) {
    int choice;
    while (true) {
        cout << "> ";
        if (cin >> choice && choice >= min && choice <= max) break;
        cout << "Invalid input. Enter a number between " << min << " and " << max << ". ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}
//Bank/Stat Menu
//Shows balance, wins/losses, and win ratio
void displayBank(Session& session) {
    Bank bank(session);

    while (true) {
        cout << "\n====== 🏦 Bank & Stats ======\n";
        cout << "💰 Balance: " << session.balance << " chips\n";
        cout << "✅ Wins: " << session.wins << "\n";
        cout << "❌ Losses: " << session.losses << "\n";
        cout << fixed << setprecision(1);
        cout << "📊 Win Ratio: " << session.getWinRatio() << "%\n";

        cout << "\nOptions:\n";
        cout << "1. Deposit Chips\n";
        cout << "2. Withdraw Chips\n";
        cout << "3. Return to Main Menu\n";
        cout << "Enter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter amount to deposit: ";
            double amount;
            if (!(cin >> amount)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (amount <= 0) {
                cout << "Deposit must be a positive number.\n";
                continue;
            }
            if (amount > 100000) {
                cout << "Maximum deposit is 100,000 chips.\n";
                continue;
            }
            
            bank.deposit(amount);
            
        }
        else if (choice == "2") {
            cout << "Enter amount to withdraw: ";
            double amount;
            if (!(cin >> amount)) {
                cout << "Invalid input. Please enter a number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bank.withdraw(amount);
        }
        else if (choice == "3") {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }
}

//Games Menu
//It lets the user pick a game to play
void displayGamesMenu(Session& session) {
    while (true) {
        cout << "\n====== 🎲 Games Menu ======\n";
        cout << "1. Blackjack\n";
        cout << "2. Dice Duel\n";
        cout << "3. Slots\n";
        
        cout << "4. Back to Main Menu\n";

        int choice = getValidatedInput(1, 4);
        switch (choice) {
            case 1: {
                cout << "🔔 Launching Blackjack...\n";
                blackjack bjack;
                bjack.play();
                break;
            }
            case 2:{
                cout << "🔔 Launching Dice Duel...\n";
                diceDuel duel(session);
                duel.start();
                break;
            }
            case 3: {
                cout << "🔔 Launching Slots...\n";
                slotMachine slots;
                slots.start();
                break;
            }
            case 4: {
                return;
            }
        }
    }
}

//Main menu
//The Main hub that links everything together
void displayMainMenu(Session& session) {
    while (true) {
        cout << "\n===============================\n";
        cout << "🎰  Welcome to C++asino!  🎰\n";
        cout << "===============================\n";
        cout << "Chips: " << session.balance << "\n";
        cout << "1. Games\n";
        cout << "2. Bank / Stats\n";
        cout << "3. Quit\n";

        int choice = getValidatedInput(1, 3);
        switch (choice) {
            case 1:
                displayGamesMenu(session);
                break;
            case 2:
                displayBank(session);
                break;
            case 3: {
                std::cout << "\nSaving data... 🗃️\n";
            
                auto users = loadUsersFromCSV("data/users.csv");
                for (auto& user : users) {
                    if (user.username == session.username) {
                        user.balance = session.balance;
                        user.wins = session.wins;
                        user.losses = session.losses;
                        break;
                    }
                }
                saveUsersToCSV(users, "data/users.csv");
            
                std::cout << "Thanks for playing!\n";
                return;
            }
                                
        }
    }
}

