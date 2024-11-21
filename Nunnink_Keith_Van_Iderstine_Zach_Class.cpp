#include <string>
#include <iostream>
#include <ctime> // Includes the <ctime> library for time-related functions
//#include "Nunnink_Keith_Van_Iderstine_Zach_Class.h"

// Constructor to initialize the User object with provided data
User::User(std::string inputName, std::string inputDOB, std::string inputEmail, std::string inputPassword)
{
    // Set user data using functions for fact checking
    setName(inputName);
    setDOB(inputDOB);
    setEmail(inputEmail);
    setPassword(inputPassword);

    failedPasswordAttempts = 0; // Initialize failed password attempts to 0 since it's a new account
    accountStatus = 1; // Set account to be unlocked (status 1) since it's a new account

    time(&lastLoginDate); // Set login date and time to current
}

// Default constructor
User::User()
{
    // Blank constructor template
    // std::cout << "This should not be used!";
}

// Setter for password with validation check
bool User::setPassword(std::string inputPassword)
{
    if(isValidInput(1, inputPassword))
    {
        password = inputPassword;
        return true;
    }
    else
    {
        return false;
    }
}

// Setter for name with placeholder for validation
void User::setName(std::string inputName)
{
    name = inputName; // Direct setting for now, need to do input validation
}

// Setter for date of birth with placeholder for validation
void User::setDOB(std::string inputDOB)
{
    dob = inputDOB; // Direct setting for now, need to do input validation
}

// Setter for email with placeholder for validation
void User::setEmail(std::string inputAddress)
{
    email = inputAddress; // Direct setting for now, need to do input validation
}

// Method to change password, requires previous password and validation
bool User::changePassword(std::string inputPassword, std::string prevPassword)
{
    if(isValidInput(1, inputPassword) && prevPassword == password)
    {
        password = inputPassword;
        return true;
    }
    else
    {
        return false;
    }
}

// Getter for name
std::string User::getName() const
{
    return name;
}

// Getter for date of birth
std::string User::getDOB() const
{
    return dob;
}

// Getter for email
std::string User::getEmail() const
{
    return email;
}

// Getter for failed password attempts
int User::getFailedPasswordAttemps() const
{
    return failedPasswordAttempts;
}

// Getter for previous failed password attempts
int User::getPrevFailedPasswordAttemps() const
{
    return prevFailedPasswordAttempts;
}

// Getter for last login date
time_t User::getLastLoginDate() const
{
    return lastLoginDate;
}

// Getter for previous last login date
time_t User::getPrevLastLoginDate() const
{
    return prevLastLoginDate;
}

// Method to unlock account, currently unlocks without admin check
bool User::unlockAccount()
{
    accountStatus = 1;
    failedPasswordAttempts = 0;
    if(accountStatus != 0)
    {
        return false; // Return false since account failed to unlock
    }
    else
    {
        return true; // Return true since account is unlocked
    }
}

// Method to attempt login and validate password
int User::attemptLogin(std::string inputPassword)
{
    if(accountStatus != 1)
    {
        return 2; // Account is not unlocked
    }
    else if(isValidInput(1, inputPassword) && inputPassword == password)
    {
        prevLastLoginDate = lastLoginDate;
        time(&lastLoginDate); // Set last login date to current

        failedPasswordAttempts = 0; // Reset failed attempts to 0
        return 1; // Return 1 for successful login
    }
    else
    {
        failedPasswordAttempts++; // Increment failed login attempts by 1

        if (failedPasswordAttempts == 3)
        {
            accountStatus = 2; // Set status to 2 for account locked
        }
        return 0; // Return 0 for failed login
    }
}

// Method to validate input based on type (1 = Password, 2 = DOB, 3 = Email, 4 = Name)
bool User::isValidInput(int type, const std::string& str)
{
    switch (type)
    {
        case 1: // Password validation
        {
            bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;

            for (char ch : str) {
                if (std::isupper(ch)) hasUpper = true;
                else if (std::islower(ch)) hasLower = true;
                else if (std::isdigit(ch)) hasDigit = true;
                else if (std::ispunct(ch)) hasSymbol = true;

                // If all conditions are met, return true
                if (hasUpper && hasLower && hasDigit && hasSymbol) return true;
            }

            return false; // If any condition is not met
        }

        case 2: // DOB validation
        {
            bool hasDigit = false, hasSymbol = false;

            for (char ch : str) {
                if (std::isdigit(ch)) hasDigit = true;
                else if (std::ispunct(ch)) hasSymbol = true;

                // If all conditions are met, return true
                if (hasDigit && hasSymbol) return true;
            }

            return false; // If any condition is not met
        }

        case 3: // Email validation
        {
            bool hasSymbol = false;

            for (char ch : str) {
                if (std::ispunct(ch)) hasSymbol = true;

                // If condition is met, return true
                if (hasSymbol) return true;
            }

            return false; // If condition is not met
        }

        case 4: // Name validation
        {
            bool hasChar = false;

            for (char ch : str) {
                if (std::isupper(ch) || std::islower(ch)) hasChar = true;

                // If condition is met, return true
                if (hasChar) return true;
            }

            return false; // If condition is not met
        }

        default:
            return false; // Return false for invalid type
    }
}

// Method to check if account is locked
bool User::isLocked()
{
    return accountStatus != 1;
