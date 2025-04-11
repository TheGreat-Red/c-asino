#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "session.h"

class GameManager {
public:
    GameManager(Session& s);
    void listGames();

private:
    Session& session;
};



#endif



