#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include "../include/csvHelper.h"

UserRecord::UserRecord(const std::string& user, int bal, int win, int loss)
    : username(user), balance(bal), wins(win), losses(loss) {}

std::vector<UserRecord> loadUsersFromCSV(const std::string& filename) {
    std::vector<UserRecord> users;
    std::ifstream file(filename);

    if (file.bad()) {
        std::cerr << "User file not found. Starting with empty user list.\n";
        return users;
    }

    std::string line, user, balanceStr, winStr, lossStr;
    getline(file, line); 

    while (getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, user, ',');
        getline(ss, balanceStr, ',');
        getline(ss, winStr, ',');
        getline(ss, lossStr, ',');
        
        UserRecord newUser(user, std::stoi(balanceStr), std::stoi(winStr), std::stoi(lossStr));
        users.push_back(newUser);
    }
    return users;
}

void saveUsersToCSV(const std::vector<UserRecord>& users, const std::string& filename) {
    std::filesystem::create_directories("data");
    
    if (!std::filesystem::exists(filename)) {
        std::cout << "Creating new user file: " << filename << "\n";
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    file << "username,balance,wins,losses\n";
    for (const auto& u : users) {
        file << u.username << "," << u.balance << "," << u.wins << "," << u.losses << '\n';
    }
}
