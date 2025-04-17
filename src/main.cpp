#include <iostream>
#include <string>

#include "../include/authManager.h"
#include "../include/mainMenu.h"
#include "../include/session.h"

int main()
{
    Session session;                    
    AuthManager auth(session);       

    while (true)
    {
        if (!auth.authMenu())
        {
            return 0; 
        }

        if (!session.username.empty())
        {
            break; 
        }

        std::cout << "Login failed. Please try again.\n";
    }

    MainMenu menu(session);            
    menu.displayMenu();

    return 0;
}
