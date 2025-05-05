#ifndef SESSION_H
#define SESSION_H

#include <string>

struct Session {
    std::string username;
    std::string password;
    double balance;

    //blank session is created below
    Session() : username(""), password(""), balance(0.0) {}

    //creates a session with given values (user,pass,balance)
    Session(const std::string& user, const std::string& pass, double initialBalance = 0.0)
        : username(user), password(pass), balance(initialBalance) {}
};


#endif
