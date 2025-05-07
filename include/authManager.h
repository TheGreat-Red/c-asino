#ifndef AUTH_MANAGER_H
#define AUTH_MANAGER_H

#include <vector>

#include "csvHelper.h"       // For UserRecord

class AuthManager {
    public:
        static bool authMenu();
        static bool login();
        static bool createAccount();
        static std::vector<UserRecord>& users;
        static UserRecord& currentUser;
};

#endif