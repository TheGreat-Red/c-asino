#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H

#include <iostream>
#include <string>
#include "../include/session.h"  
#include "../include/bankManager.h"  

class slotMachine {
public:
    //Reference to the user's session
    Session& userSession;

    //Constructor: Initializes userSession
    slotMachine(Session& s);

    void start();
};

#endif