
#include "../include/User.h"
#include <iostream>

User::User(const std::string& id, const std::string& userName, const std::string& pwd)
    : userID(id), name(userName), password(pwd) {
}

bool User::authenticate(const std::string& attemptedPassword) const {
    // In a real implementation, this would compare hashed passwords
    return password == attemptedPassword;
}

std::string User::getUserDetails() const {
    return "User ID: " + userID + ", Name: " + name;
}

std::string User::getUserID() const {
    return userID;
}

std::string User::getName() const {
    return name;
}

bool User::changePassword(const std::string& oldPassword, const std::string& newPassword) {
    // Verify the old password is correct
    if (authenticate(oldPassword)) {
        password = newPassword;
        return true;
    }
    return false;
}