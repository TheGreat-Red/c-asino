#ifndef MAIN_MENU_H
#define MAIN_MENU_H


#include "session.h"

class MainMenu
{
    public:
        MainMenu(Session& s);
        void displayMenu();


    private:
        Session& session;
};




#endif