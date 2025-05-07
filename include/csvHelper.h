#ifndef CSVHELPER_H
#define CSVHELPER_H

#include <string>
#include <vector>
#include <filesystem>

class UserRecord {
public:
    UserRecord(const std::string& user, int bal, int win, int loss);

    std::string username;
    int balance;
    int wins;
    int losses;

    float getWinRatio() const {
        int total = wins + losses;
        return (total != 0) ? (float(wins) / total) * 100.0f : 0.0f;
    }
};

std::vector<UserRecord> loadUsersFromCSV(const std::string& filename);

void saveUsersToCSV(const std::vector<UserRecord>& users, const std::string& filename);

#endif