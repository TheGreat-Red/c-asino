#ifndef CASINO_UI_H
#define CASINO_UI_H

#include <iostream>

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


void displayMainMenu(Player& player);
void displayGamesMenu(Player& player);
void displayBank(Player& player);


int getValidatedInput(int min, int max);

#endif
