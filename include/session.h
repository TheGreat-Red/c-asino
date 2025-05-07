#ifndef SESSION_H
#define SESSION_H

#include <string>

struct Session {
    std::string username;
    std::string password;
    double balance;

    int wins = 0;
    int losses = 0;

    Session() : username(""), password(""), balance(0.0), wins(0), losses(0) {}
    Session(const std::string& user, const std::string& pass, double initialBalance = 0.0)
        : username(user), password(pass), balance(initialBalance), wins(0), losses(0) {}

    float getWinRatio() const {
        int total = wins + losses;
        return (total == 0) ? 0.0f : (float(wins) / total) * 100.0f;
    }
};



#endif
