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
    void deposit(double amount);
    void withdraw(double amount);    
    bool bet();
    void addFunds(double amount);
    void subtractFunds(double amount);

private:
    Session& session;
    double currentWager = 0.0;
};



#endif