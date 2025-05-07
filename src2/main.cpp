#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

//PLAYER STRUCT
//Replace this with Mike's full Player class when ready
struct Player {
    int balance = 100;
    int wins = 3;
    int losses = 5;

    float getWinRatio() const {
        int total = wins + losses;
        return (total == 0) ? 0.0f : (float(wins) / total) * 100.0f;
    }
};
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
void displayBank(Player& player) {
    cout << "\n====== 🏦 Bank & Stats ======\n";
    cout << "💰 Balance: " << player.balance << " chips\n";
    cout << "✅ Wins: " << player.wins << "\n";
    cout << "❌ Losses: " << player.losses << "\n";
    cout << fixed << setprecision(1);
    cout << "📊 Win Ratio: " << player.getWinRatio() << "%\n";
    cout << "\nPress ENTER to return...";
    cin.ignore();
    cin.get();
}
//Games Menu
//It lets the user pick a game to play
void displayGamesMenu(Player& player) {
    while (true) {
        cout << "\n====== 🎲 Games Menu ======\n";
        cout << "1. Blackjack\n";
        cout << "2. Dice Duel\n";
        cout << "3. Slots\n";
        
        cout << "0. Back to Main Menu\n";

        int choice = getValidatedInput(1, 4);
        switch (choice) {
            case 1:
                cout << "🔔 Launching Blackjack...\n";
                //Nic's blackjack game function goes here
                break;
            case 2:
                cout << "🔔 Launching Dice Duel...\n";
                //Add Elijah’s game here
                break;
            case 3:
                cout << "🔔 Launching Slots...\n";
                //Add another game here if needed
                break;
            case 0:
                return;
        }
    }
}

//Main menu
//The Main hub that links everything together
void displayMainMenu(Player& player) {
    while (true) {
        cout << "\n===============================\n";
        cout << "🎰  Welcome to C++asino!  🎰\n";
        cout << "===============================\n";
        cout << "Chips: " << player.balance << "\n";
        cout << "1. Games\n";
        cout << "2. Bank / Stats\n";
        cout << "3. Quit\n";

        int choice = getValidatedInput(1, 3);
        switch (choice) {
            case 1:
                displayGamesMenu(player);
                break;
            case 2:
                displayBank(player);
                break;
            case 3:
                cout << "\nSaving data... 🗃️\n";
                cout << "Thanks for playing!\n";
                return; //Exits the program
        }
    }
}

//Main function
//Starts the program with a test player
int main() {
    Player player;
    displayMainMenu(player);
    return 0;
}

