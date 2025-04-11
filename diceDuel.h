#ifndef DICE_DUEL_H
#define DICE_DUEL_H

#include "session.h"
#include "bankManager.h"

class diceDuel {
    public:
        diceDuel(Session& s);     
        void start();
        void randomLogic(Bank& bank);
    
    private:
        Session& session;         
    };
    



#endif



