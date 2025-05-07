#ifndef CASINO_UI_H
#define CASINO_UI_H

#include "session.h" 

// Menu functions
void displayMainMenu(Session& session);
void displayGamesMenu(Session& session);
void displayBank(Session& session);

// Utility
int getValidatedInput(int min, int max);

#endif
