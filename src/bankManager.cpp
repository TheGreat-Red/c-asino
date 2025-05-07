#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "../include/bankManager.h"
#include "../include/authManager.h"
#include "../include/csvHelper.h"

Bank::Bank(Session& s) : session(s) {}



/*void Bank::bankScreen()
{
    while(true)
    {    
        std::cout<< "\n" << session.username << "\n";
        std::cout<< R"(
    1. View Balance
    2. Deposit Money
    3. Withdraw Money
    4. Back
        )"; std::cout<<std::endl;

        std::string input;

        getline(std::cin, input);
        try
        {
            if (stoi(input) == 1)
            {
                double currentBalance = getBalance();
                std::cout<< currentBalance;
            }
            else if (stoi(input) == 2)
            {
                deposit();
            }
            else if (stoi(input) == 3)
            {
                withdraw();
            }
            else if (stoi(input) == 4)
            {
                break;
            }
            else  
            {
                std::cout<< "Invalid Choice";
                continue;
            }
        } 
        catch (...)
        {
            std::cout<< "Please enter a valid number";
        }
    }
}
*/
void Bank::addFunds(double amount) {
    auto users = loadUsersFromCSV("data/users.csv");

    for (auto& user : users) {
        if (user.username == session.username) {
            user.balance += amount;
            session.balance = user.balance;
            std::cout << "Funds added: " << amount << "\n";
            break;
        }
    }

    saveUsersToCSV(users, "data/users.csv");
}

void Bank::subtractFunds(double amount) {
    auto users = loadUsersFromCSV("data/users.csv");

    for (auto& user : users) {
        if (user.username == session.username) {
            if (user.balance >= amount) {
                user.balance -= amount;
                session.balance = user.balance;
                std::cout << "Funds subtracted: " << amount << "\n";
            } else {
                std::cout << "Insufficient funds to subtract " << amount << "\n";
            }
            break;
        }
    }

    saveUsersToCSV(users, "data/users.csv");
}

double Bank::getBalance() {
    auto users = loadUsersFromCSV("data/users.csv");
    for (const auto& user : users) {
        if (user.username == session.username) {
            return user.balance;
        }
    }
    std::cout << "ERROR: USER NOT FOUND\n";
    return -1;
}

void Bank::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Deposit must be a positive amount\n";
        return;
    }

    auto users = loadUsersFromCSV("data/users.csv");

    for (auto& user : users) {
        if (user.username == session.username) {
            user.balance += amount;
            session.balance = user.balance;
            std::cout << "Deposit of " << amount << " processed.\n";
            break;
        }
    }

    saveUsersToCSV(users, "data/users.csv");
}

void Bank::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Withdrawal must be a positive amount\n";
        return;
    }

    auto users = loadUsersFromCSV("data/users.csv");

    for (auto& user : users) {
        if (user.username == session.username) {
            if (user.balance >= amount) {
                user.balance -= amount;
                session.balance = user.balance;
                std::cout << "Withdrawal of " << amount << " processed.\n";
            } else {
                std::cout << "Insufficient funds.\n";
            }
            break;
        }
    }

    saveUsersToCSV(users, "data/users.csv");
}




void Bank::win()
{
    auto users = loadUsersFromCSV("data/users.csv");
    for (auto& user : users) {
        if (user.username == session.username) {
            user.balance += currentWager;
            session.balance = user.balance;
            std::cout << "Winnings added\n";
            break;
        }
    }
    saveUsersToCSV(users, "data/users.csv");
}


void Bank::lose()
{
    auto users = loadUsersFromCSV("data/users.csv");
    for (auto& user : users) {
        if (user.username == session.username) {
            user.balance -= currentWager;
            session.balance = user.balance;
            std::cout << "Wager lost of " << currentWager << "\n";
            break;
        }
    }
    saveUsersToCSV(users, "data/users.csv");
}


bool Bank::bet()
{
    std::string wagerAmount;
    double wager;

    while (true)
    {

    
        std::cout << "Enter wager: \n";
        getline(std::cin, wagerAmount);


        try
        {
            wager = stod(wagerAmount);
            if (wager < 0) 
            {
                std::cout << "Wager is negative...\n";
                continue;
            } 
        }
        catch(const std::exception& e)
        {
            std::cout<< "Invalid input. Please enter a number";
            continue;
        }
        break;

    }
    

    auto users = loadUsersFromCSV("data/users.csv");
    for (const auto& user : users) {
        if (user.username == session.username) {
            if (wager <= user.balance) {
                this->currentWager = wager;
                return true;
            } else {
                return false;
            }
        }
    }

    std::cout << "ERROR: user not found\n";
    return false;
}
