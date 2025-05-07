#include <iostream>
#include <limits>
#include <iomanip>

#include "../include/casinoUi.h"
#include "../include/csvHelper.h"
#include "../include/authManager.h"
#include "../include/blackjack.h"
#include "../include/diceDuel.h"
#include "../include/slotMachine.h"

using namespace std;

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
void displayBank() {
    auto user = AuthManager::currentUser;
    cout << "\n====== 👤 Player Balance & Stats ======\n";
    cout << "💰 Balance: " << user.balance << " chips\n";
    cout << "✅ Wins: " << user.wins << "\n";
    cout << "❌ Losses: " << user.losses << "\n";
    cout << fixed << setprecision(1);
    cout << "📊 Win Ratio: " << user.getWinRatio() << "%\n";
    cout << "\nPress ENTER to return...";
    cin.ignore();
    cin.get();
}
//Games Menu
//It lets the user pick a game to play
void displayGamesMenu() {
    while (true) {
        cout << "\n====== 🎲 Games Menu ======\n";
        cout << "1. Blackjack\n";
        cout << "2. Dice Duel\n";
        cout << "3. Slots\n";
        cout << "0. Back to Main Menu\n";

        int choice = getValidatedInput(1, 4);
        switch (choice) {
            case 1: {
                cout << "🔔 Launching Blackjack...\n";
                Blackjack bjack;
                bjack.play();
                break;
            }

            case 2:{
                cout << "🔔 Launching Dice Duel...\n";
                DiceDuel duel;
                duel.start();
                break;
            }

            case 3: {
                cout << "🔔 Launching Slots...\n";
                SlotMachine slots;
                slots.start();
                break;
            }

            case 0: {
                return;
            }
        }
    }
}

//Main menu
//The Main hub that links everything together
void displayMainMenu() {
    while (true) {
        cout << "\n===============================\n";
        cout << "🎰  Welcome to C++asino!  🎰\n";
        cout << "===============================\n";
        cout << "Chips: " << AuthManager::currentUser.balance << "\n";
        cout << "1. Games\n";
        cout << "2. Bank / Stats\n";
        cout << "3. Quit\n";

        int choice = getValidatedInput(1, 3);
        switch (choice) {
            case 1:
                displayGamesMenu();
                break;
            case 2:
                displayBank();
                break;
            case 3:
                cout << "\nSaving data... 🗃️\n";
                cout << "Thanks for playing!\n";
                return; //Exits the program
        }
    }
}

