//
// Created by jasmine nwajei on 21/04/2025.
//

#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string userID;
    std::string name;
    std::string password; // In a real application, this would be hashed

public:
    User(const std::string& id, const std::string& userName, const std::string& pwd);
    virtual ~User() = default;

    virtual bool authenticate(const std::string& attemptedPassword) const;
    virtual std::string getUserDetails() const;

    std::string getUserID() const;
    std::string getName() const;
};

#endif // USER_H