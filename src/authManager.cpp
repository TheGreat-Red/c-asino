#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/authManager.h"
#include "../include/csvHelper.h"

AuthManager::AuthManager(Session& s) : session(s) {}

bool AuthManager::authMenu()
{
    while (true)
    {
        std::cout << R"(
        1. Login
        2. Register
        3. Exit)";
        std::cout << std::endl;

        std::string input;
        getline(std::cin, input);

        if (input == "1")
        {
            if (login())
                return true;
        }
        else if (input == "2")
        {
            if (createAccount())
                return true;
        }
        else if (input == "3")
        {
            return false;
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }
}

bool AuthManager::login()
{
    const std::string filepath = "data/users.csv";


    if (!std::filesystem::exists(filepath)) {
        std::cout << "No user database found. Please register first.\n";
        return false;
    }

    std::string username, password;
    std::cout << "Enter your username: ";
    getline(std::cin, username);
    std::cout << "Enter your password: ";
    getline(std::cin, password);

    if (username.empty() || password.empty()) {
        std::cout << "Username or password cannot be empty.\n";
        return false;
    }

    auto users = loadUsersFromCSV(filepath);

    for (const auto& user : users)
    {
        if (user.username == username && user.password == password)
        {
            session.username = user.username;
            session.password = user.password;
            session.balance = user.balance;
            session.wins = user.wins;
            session.losses = user.losses;
            

            std::cout << "Access granted. Welcome " << username << "\n";
            return true;
        }
    }

    std::cout << "Login failed. Please try again.\n";
    return false;
}


bool AuthManager::createAccount()
{
    std::string username, password;
    std::cout << "Enter new username: ";
    getline(std::cin, username);
    std::cout << "Enter new password: ";
    getline(std::cin, password);

    if (username.empty() || password.empty()) {
        std::cout << "Username or password cannot be empty.\n";
        return false;
    }

    if (username.find(',') != std::string::npos || password.find(',') != std::string::npos) {
        std::cout << "Commas are not allowed in username/password.\n";
        return false;
    }

    const std::string filepath = "data/users.csv";
    auto users = loadUsersFromCSV(filepath);

    for (const auto& user : users)
    {
        if (user.username == username)
        {
            std::cout << "Username already exists.\n";
            return false;
        }
    }

    UserRecord newUser(username, password, 100.0, 0, 0);
    users.push_back(newUser);
    saveUsersToCSV(users, filepath);

    std::cout << "Account created. You are now logged in.\n";
    session.username = username;
    session.password = password;
    session.balance = 100.0;
    session.wins = 0;
    session.losses = 0;    

    return true;
}
