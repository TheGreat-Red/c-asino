#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/AuthManager.h"
#include "../include/csvHelper.h"


bool AuthManager::authMenu()
{
    while (true)
    {
        std::cout << "1. Login\n2. Register\n3. Exit";
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

    std::string username;
    std::cout << "Enter your username: ";
    getline(std::cin, username);

    if (username.empty()) {
        std::cout << "Username cannot be empty.\n";
        return false;
    }

    users = loadUsersFromCSV(filepath);

    for (const auto& user : users)
    {
        if (user.username == username)
        {
            currentUser = user;

            std::cout << "Access granted. Welcome " << username << "\n";
            return true;
        }
    }

    std::cout << "Login failed. Please try again.\n";
    return false;
}


bool AuthManager::createAccount()
{
    std::string username;
    std::cout << "Enter new username: ";
    getline(std::cin, username);

    if (username.empty()) {
        std::cout << "Username cannot be empty.\n";
        return false;
    }

    if (username.find(',') != std::string::npos) {
        std::cout << "Commas are not allowed in username.\n";
        return false;
    }

    const std::string filepath = "data/users.csv";
    users = loadUsersFromCSV(filepath);

    for (const auto& user : users)
    {
        if (user.username == username)
        {
            std::cout << "Username already exists.\n";
            return false;
        }
    }

    UserRecord newUser(username, 100, 0, 0);
    users.push_back(newUser);
    saveUsersToCSV(users, filepath);
    currentUser = users.back();

    std::cout << "Account created. You are now logged in.\n";

    return true;
}
