#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include "session.h"         // Ensure this defines struct/class Session
#include "csvHelper.h"       // For UserRecord

class AuthManager {
public:
    AuthManager(Session& s);
    bool authMenu();
    bool login();
    bool createAccount();



private:
    Session& session;
};

#endif