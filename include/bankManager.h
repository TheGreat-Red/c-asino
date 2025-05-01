#ifndef BANK_MANAGER_H
#define BANK_MANAGER_H

#include "session.h" 

class Bank {
public:
    Bank(Session& s);
    void bankScreen();
    double getBalance();
    void win();
    void lose();
    void withdraw();
    void deposit();
    bool bet();
    void addFunds(double amount);
    void subtractFunds(double amount);

private:
    Session& session;
    double currentWager = 0.0;
};



#endif