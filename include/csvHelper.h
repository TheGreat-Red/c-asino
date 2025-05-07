#ifndef CSVHELPER_H
#define CSVHELPER_H


#include <string>
#include <vector>
#include <filesystem>

class UserRecord {
    public:
        std::string username;
        std::string password;
        double balance;
        int wins;
        int losses;
    
        UserRecord(); 
        UserRecord(const std::string& user, const std::string& pass, double bal, int w = 0, int l = 0);
    };
    

std::vector<UserRecord> loadUsersFromCSV(const std::string& filename);
void saveUsersToCSV(const std::vector<UserRecord>& users, const std::string& filename);


#endif