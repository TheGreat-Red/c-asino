#include "../include/csvHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

UserRecord::UserRecord() : username(""), password(""), balance(0.0) {}

UserRecord::UserRecord(const std::string& user, const std::string& pass, double bal, int w, int l)
    : username(user), password(pass), balance(bal), wins(w), losses(l) {}


std::vector<UserRecord> loadUsersFromCSV(const std::string& filename) {
    std::vector<UserRecord> users;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "User file not found. Starting with empty user list.\n";
        return users;
    }

    std::string line;
    getline(file, line); 

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string user, pass, balanceStr, winsStr, lossesStr;
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, balanceStr, ',');
        getline(ss, winsStr, ',');
        getline(ss, lossesStr);
        
        try {
            double bal = std::stod(balanceStr);
            int w = std::stoi(winsStr);
            int l = std::stoi(lossesStr);
            users.emplace_back(user, pass, bal, w, l);
            
        } catch (...) {
            std::cerr << "Invalid balance on line: " << line << "\n";
        }
    }
    return users;
}

void saveUsersToCSV(const std::vector<UserRecord>& users, const std::string& filename) {
    std::filesystem::create_directories("data");


    bool fileExists = std::filesystem::exists(filename);
    if (!fileExists) {
        std::cout << "Creating new user file: " << filename << "\n";
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    file << "username,password,balance,wins,losses\n";
    for (const auto& u : users) {
        file << u.username << "," << u.password << "," << u.balance << "," << u.wins << "," << u.losses << "\n";

    }
}
