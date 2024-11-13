//Coder/Developer: Keith Nunnink & Zach Van Iderstine
//Class: COP 2006-80599, Fall 2024
//Date:October 2nd, 2024
//Description: C++ program to create user registration and login system
//Log: 10/01/2024: Zach started defining classes for program
//Log: 10/02/2024: Keith started working on gui/work flow code
//Log: 10/15/2024: Keith worked on code some more
//Log: 10/31/2024: Keith worked on code
//Log: 11/05/2024: Keith and Zach worked on finalizing code
//Log: 11/07/2024: Keith added unlock account and display users option
//Log: 11/12/2024: Zach added verification to create a new user before the constructor. Moved the user map from global to main() and passed the user map into all the functions


#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>

// Function declarations:
void registerUser(std::unordered_map<std::string, User>& users);
bool loginUser(std::unordered_map<std::string, User>& users);
bool menuLoggedIn(const std::string& username, std::unordered_map<std::string, User>& users);
bool displayLastLogins(const std::string& username, std::unordered_map<std::string, User>& users);
bool changePassword(const std::string& username, std::unordered_map<std::string, User>& users);
bool unlockAccount(std::unordered_map<std::string, User>& users);
void displayAllUsernames(const std::unordered_map<std::string, User>& users);

int main()
{
    // Unordered map to store users
    std::unordered_map<std::string, User> users;

    while (true) {
        int choice = 0;
        std::cout << "\n1. Register\n2. Login\n3. Unlock Account\n4. Display All Users\n5. Exit\nChoose an option: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignores the newline character left in the buffer

        switch (choice) {
        case 1:
            registerUser(users);
            break;
        case 2:
            loginUser(users);
            break;
        case 3:
            unlockAccount(users);
            break;
        case 4:
            displayAllUsernames(users);
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Register a new user
void registerUser(std::unordered_map<std::string, User>& users) {
    std::string name, dob, address, username, password;
    User verify;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    while (!verify.isValidInput(4, name))
    {
        std::cout << "Name was invalid plase try again! \n";
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
    }
    std::cout << "Enter your date of birth (DD/MM/YYYY): ";
    std::getline(std::cin, dob);
    while (!verify.isValidInput(2, dob))
    {
        std::cout << "Name was invalid plase try again! \n";
        std::cout << "Enter your date of birth (DD/MM/YYYY): ";
        std::getline(std::cin, dob);
    }
    std::cout << "Enter your email address: ";
    std::getline(std::cin, address);
    while (!verify.isValidInput(3, address))
    {
        std::cout << "Name was invalid plase try again! \n";
        std::cout << "Enter your email address: ";
        std::getline(std::cin, address);
    }

    bool usernameExists = false;
    do {
        std::cout << "Create a username: ";
        std::getline(std::cin, username);
        if (users.find(username) != users.end()) {
            std::cout << "Username already exists. Please choose a different username.\n";
            usernameExists = true;
        } else {
            usernameExists = false;
        }
    } while (usernameExists);

    std::cout << "Create a password: ";
    std::getline(std::cin, password);
    while (!verify.isValidInput(1, password))
    {
        std::cout << "Name was invalid plase try again! Password must have 1 upper case, 1 lower case, 1 symbol and 1 number! \n";
        std::cout << "Create a password: ";
        std::getline(std::cin, password);
    }

    User newUser(name, dob, address, password);
    users[username] = newUser;
    std::cout << "Registration successful!\n";
    menuLoggedIn(username, users); // Show menu after successful registration
}

// Log in a user
bool loginUser(std::unordered_map<std::string, User>& users) {
    std::string username, password;

    std::cout << "Enter your username: ";
    std::getline(std::cin, username);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    if (users.find(username) != users.end()) {
        int loginResult = users[username].attemptLogin(password);
        if (loginResult == 1) {
            time_t loginTime = users[username].getPrevLastLoginDate();
            std::cout << "Login successful! Welcome, " << users[username].getName()
                      << ". Last login was: " << ctime(&loginTime);
            menuLoggedIn(username, users);
            return true;
        } else if (loginResult == -1) {
            std::cout << "Account is locked due to too many failed login attempts. Please unlock your account.\n";
            return false; // Account is locked, do nothing more
        } else {
            std::cout << "Invalid password.\n";
            return false;
        }
    } else {
        std::cout << "Invalid username.\n";
        return false;
    }
}

// Display user menu after logging in
bool menuLoggedIn(const std::string& username, std::unordered_map<std::string, User>& users) {
    int choice;
    bool exit = false;
    while (!exit) {
        std::cout << "Please select one of the following choices:\n"
                     "1: Change password\n"
                     "2: Display last 2 login dates/times\n"
                     "3: Logout\n";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            changePassword(username, users);
            break;
        case 2:
            displayLastLogins(username, users);
            break;
        case 3:
            exit = true;
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }
    return true;
}

// Display the last two login dates/times
bool displayLastLogins(const std::string& username, std::unordered_map<std::string, User>& users) {
    time_t loginTime1 = users[username].getLastLoginDate();
    time_t loginTime2 = users[username].getPrevLastLoginDate();
    std::cout << "The last 2 login times were:\n" << ctime(&loginTime1) << "and\n" << ctime(&loginTime2);
    return true;
}

// Change the password for a user
bool changePassword(const std::string& username, std::unordered_map<std::string, User>& users)
{
    std::string currentPassword, newPassword;
    std::cout << "Please enter current password: ";
    std::cin >> currentPassword;
    std::cout << "Please enter the new password: ";
    std::cin >> newPassword;
    std::cin.ignore();

    if (users[username].changePassword(newPassword, currentPassword)) {
        std::cout << "Password changed!\n";
    } else {
        std::cout << "Password was not changed!\n";
    }
    return true;
}

// Unlock a user's account with date of birth verification
bool unlockAccount(std::unordered_map<std::string, User>& users)
{
    std::string username, dob;
    std::cout << "Enter the username to unlock: ";
    std::getline(std::cin, username);

    if (users.find(username) != users.end()) {
        if (!users[username].isLocked()) {
            std::cout << "Account is not locked.\n";
            return false;
        }

        std::cout << "Enter date of birth for verification (DD/MM/YYYY): ";
        std::getline(std::cin, dob);

        if (users[username].getDOB() == dob) {
            users[username].unlockAccount();
            return true;
        } else {
            std::cout << "Date of birth does not match. Unable to unlock the account.\n";
            return false;
        }
    } else {
        std::cout << "User not found.\n";
        return false;
    }
}

// Display all usernames
void displayAllUsernames(const std::unordered_map<std::string, User>& users) {
    if (users.empty()) {
        std::cout << "No users registered.\n";
        return;
    }
    std::cout << "Registered usernames:\n";
    for (const auto& userPair : users) {
        std::cout << "- " << userPair.first << "\n";
    }
}
