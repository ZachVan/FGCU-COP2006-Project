#include <string>
#include <iostream>
#include <ctime> //From: https://www.w3schools.com/cpp/cpp_date.asp
//#include "Nunnink_Keith_Van_Iderstine_Zach_Class.h"

//Constructor
User::User(std::string inputName, std::string inputDOB, std::string inputEmail, std::string inputPassword)
{
    //Set user data using functions for fact checking
    setName(inputName);
    setDOB(inputDOB);
    setEmail(inputEmail);
    setPassword(inputPassword);

    failedPasswordAttempts = 0; //Setting failed attempts to 0 since it's a new account
    accountStatus = 1; //Setting account to be unlocked since it's a new account
    
    time(&lastLoginDate); //Set login date and time to current
}

User::User()
{
    //Blank Contrustor temp
    //std::cout << "This should not be used!";
}

//Sets
bool User::setPassword(std::string inputPassword)
{
    //
    if(isValidInput(1, inputPassword))
    {
        password = inputPassword;
        return true;
    } else {
        return false;
    }
}

void User::setName(std::string inputName)
{
    //direct setting for now, need to do input validation
    name = inputName;
}
void User::setDOB(std::string inputDOB)
{
    //direct setting for now, need to do input validation
    dob = inputDOB;
}
void User::setEmail(std::string inputAddress)
{
    //direct setting for now, need to do input validation
    email = inputAddress;
}
bool User::changePassword(std::string inputPassword, std::string prevPassword)
{
    //If user is not locked and current password is correct set a new password.

    if(isValidInput(1, inputPassword) == true && prevPassword == password)
    {
        password = inputPassword;
        return true;
    } else 
    {
        return false;
    }
}

//Gets
std::string User::getName() const
{
    return name;
}
std::string User::getDOB() const
{
    return dob;
}
std::string User::getEmail() const
{
    return email;
}
int User::getFailedPasswordAttemps() const
{
    return failedPasswordAttempts;
}
int User::getPrevFailedPasswordAttemps() const
{
    return prevFailedPasswordAttempts;
}
time_t User::getLastLoginDate() const
{
    return lastLoginDate;
}
time_t User::getPrevLastLoginDate() const
{
    return prevLastLoginDate;
}


bool User::unlockAccount()
{
    //If account is locked and user requesting the unlock is an admin unlock account.

    //setting direct for now, need to change latter:
    accountStatus = 1;
    failedPasswordAttempts = 0;
    if(accountStatus != 0)
    {
        //Return false since account failed to unlock
        return false;
    } else
    {
        //return true since account is unlocked;
        return true;
    }
}
int User::attemptLogin(std::string inputPassword)
{
    //Take in a password and verify it against the current one. If incorrect inc failed attemps by 1, if correct move failed to prev and return true.
    if(accountStatus != 1)
    {
        return 2; //Account it not unlocked
    } else if(isValidInput(1, inputPassword) && inputPassword == password)
    {
        //Set last login date
        prevLastLoginDate = lastLoginDate;
        time(&lastLoginDate);

        //Reset failed attemps to 0
        failedPasswordAttempts = 0;

        return 1; //Return 1 for account login
    } else 
    {
        //Inc failed logins by 1
        failedPasswordAttempts++;
        //Check to see if 3 failed attemps happened
        if (failedPasswordAttempts == 3)
        {
            accountStatus = 2; // Set status to 2 for account locked
        }
        return 0;
    }
}

bool User::isValidInput(int type, const std::string& str) //Taking type as a int since C++ can't switch off of strings.
/*
Legend on switch:
1 = Password
2 = DOB
3 = Email
4 = Name
*/
{
    //
    switch (type)
    {
    case 1: //Password
        {
            bool hasUpper = false;
            bool hasLower = false;
            bool hasDigit = false;
            bool hasSymbol = false;

            for (char ch : str) {
                if (std::isupper(ch)) {
                    hasUpper = true;
                } else if (std::islower(ch)) {
                    hasLower = true;
                } else if (std::isdigit(ch)) {
                hasDigit = true;
                } else if (std::ispunct(ch)) {
                    hasSymbol = true;
                }

                // If all conditions are met, we can return early
                if (hasUpper && hasLower && hasDigit && hasSymbol) {
                    return true;
                }
            }

            return false;  // If any condition is not met
            break; // This should never run since it returns first but still nice to have
        }
        
        case 2: //DOB
        {
            bool hasDigit = false;
            bool hasSymbol = false;

            for (char ch : str) {
                if (std::isdigit(ch)) {
                    hasDigit = true;
                } else if (std::ispunct(ch)) {
                    hasSymbol = true;
                }

                // If all conditions are met, we can return early
                if (hasDigit && hasSymbol) {
                    return true;
                }
            }

            return false;  // If any condition is not met
            break; // This should never run since it returns first but still nice to have
        }

        case 3: //Email
        {
            bool hasSymbol = false;

            for (char ch : str) {
                if (std::ispunct(ch)) {
                    hasSymbol = true;
                }

                // If all conditions are met, we can return early
                if (hasSymbol) {
                    return true;
                }
            }

            return false;  // If any condition is not met
            break; // This should never run since it returns first but still nice to have
        }
        case 4: //Name
        {
            bool hasChar = false;

            for (char ch : str) {
                if (std::isupper(ch)) {
                    hasChar = true;
                } else if (std::islower(ch)) {
                    hasChar = true;
                }

                // If all conditions are met, we can return early
                if (hasChar) {
                    return true;
                }

            return true;  // If any condition is not met
            break; // This should never run since it returns first but still nice to have
            }
        }
    
    default:
        return false; //This should only run if input is not valid AKA not 1 2 or 3
        break;
    }
}

bool User::isLocked()
{
    if(accountStatus == 1)
    {
        return false;
    } else 
    {
        return true;
    }
}
