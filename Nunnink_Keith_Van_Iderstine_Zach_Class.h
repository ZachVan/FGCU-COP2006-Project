//
// Created by Keith Nunnink on 11/7/2024.
//
//Something here
#ifndef USER_H
#define USER_H

#include <string>
#include <ctime>

class User
{
    private:
    std::string name; // User's name
    std::string dob; // User's date of birth
    std::string email; // User's address
    std::string password = ""; // User's password
    int failedPasswordAttempts;
    int prevFailedPasswordAttempts;
    time_t lastLoginDate;
    time_t prevLastLoginDate;
    int accountStatus; //Stores account status, 1 for unlocked 2 for locked.

    bool setPassword(std::string inputPassword);
    

    public:
    User();
    User(std::string inputName, std::string inputDOB, std::string inputEmail, std::string inputPassword);

    void setName(std::string inputName);
    void setDOB(std::string inputDOB);
    void setEmail(std::string inputAddress);
    bool changePassword(std::string inputPassword, std::string prevPassword);
    bool changePasswordAdmin(std::string inputPassword);

    std::string getName() const;
    std::string getDOB() const;
    std::string getEmail() const;
    int getFailedPasswordAttemps() const;
    int getPrevFailedPasswordAttemps() const;
    time_t getLastLoginDate() const;
    time_t getPrevLastLoginDate() const;
    int getAccountStatus() const;
    bool unlockAccount();
    int attemptLogin(std::string inputPassword); //0 = falid, 1 = sucecess, 2 = locked acocunt

    //bool isValidPassword(const std::string& str);
    bool isValidInput(int type, const std::string& str);
    bool isLocked();
};

#endif // USER_H

#include "Nunnink_Keith_Van_Iderstine_Zach_Class.cpp"