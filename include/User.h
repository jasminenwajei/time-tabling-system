

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>

/**
 * @class User
 * @brief Abstract base class for all user types in the timetabling system
 *
 * The User class provides common functionality for authentication and user
 * information management. It serves as the base class for both Admin and Student.
 */
class User {
protected:
    std::string userID;
    std::string name;
    std::string password; // In a real system, this would be stored securely (hashed and salted)

public:
    /**
     * @brief Constructor for User class
     * @param id User ID
     * @param userName User's name
     * @param pwd User's password
     */
    User(const std::string& id, const std::string& userName, const std::string& pwd);

    /**
     * @brief Virtual destructor
     */
    virtual ~User() = default;

    /**
     * @brief Authenticates user with provided password
     * @param attemptedPassword Password to verify
     * @return True if authentication successful, false otherwise
     */
    bool authenticate(const std::string& attemptedPassword) const;

    /**
     * @brief Gets user details as a string (virtual for polymorphism)
     * @return String containing user information
     */
    virtual std::string getUserDetails() const;

    /**
     * @brief Gets the user ID
     * @return User ID string
     */
    std::string getUserID() const;

    /**
     * @brief Gets the user's name
     * @return User's name string
     */
    std::string getName() const;

    /**
     * @brief Change user's password
     * @param oldPassword Current password
     * @param newPassword New password
     * @return True if password changed successfully, false otherwise
     */
    bool changePassword(const std::string& oldPassword, const std::string& newPassword);
};

#endif // USER_H