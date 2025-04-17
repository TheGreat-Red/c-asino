#include "../include/csvHelper.h"
#include <fstream>
#include <sstream>
#include <iostream>

UserRecord::UserRecord() : username(""), password(""), balance(0.0) {}

UserRecord::UserRecord(const std::string& user, const std::string& pass, double bal)
    : username(user), password(pass), balance(bal) {}

std::vector<UserRecord> loadUsersFromCSV(const std::string& filename) {
    std::vector<UserRecord> users;
    std::ifstream file(filename);

    std::string line;

    getline(file, line);
    
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string user, pass, balanceStr;
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, balanceStr);
        try {
            double bal = std::stod(balanceStr);
            users.emplace_back(user, pass, bal);
        } catch (...) {
            std::cerr << "Invalid balance on line: " << line << "\n";
        }
    }
    return users;
}

void saveUsersToCSV(const std::vector<UserRecord>& users, const std::string& filename) {
    std::ofstream file(filename);
    file << "username,password,balance\n";

    for (const auto& u : users) {
        file << u.username << "," << u.password << "," << u.balance << "\n";
    }
}
