//
// Created by jasmine nwajei on 23/04/2025.
//

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "User.h"
#include "Admin.h"
#include "Student.h"

/**
 * @class UserManager
 * @brief Manages user authentication and registration in the timetabling system
 *
 * The UserManager class handles user creation, authentication, and retrieval.
 */
class UserManager {
private:
    std::vector<User*> users;

public:
    /**
     * @brief Constructor for UserManager class
     */
    UserManager();

    /**
     * @brief Destructor to clean up owned user objects
     */
    ~UserManager();

    /**
     * @brief Authenticates a user with credentials
     * @param userId User ID
     * @param password User password
     * @return Pointer to authenticated user, or nullptr if authentication failed
     */
    User* authenticate(const std::string& userId, const std::string& password) const;

    /**
     * @brief Registers a new admin user
     * @param id Admin ID
     * @param name Admin name
     * @param password Admin password
     * @param department Admin department
     * @return Pointer to created admin, or nullptr if registration failed
     */
    Admin* registerAdmin(const std::string& id, const std::string& name,
                        const std::string& password, const std::string& department);

    /**
     * @brief Registers a new student user
     * @param id Student ID
     * @param name Student name
     * @param password Student password
     * @param studentNumber Student registration number
     * @param course Student course
     * @return Pointer to created student, or nullptr if registration failed
     */
    Student* registerStudent(const std::string& id, const std::string& name,
                            const std::string& password, const std::string& studentNumber,
                            const std::string& course);

    /**
     * @brief Gets a user by ID
     * @param userId User ID to find
     * @return Pointer to user if found, or nullptr if not found
     */
    User* getUserById(const std::string& userId) const;

    /**
     * @brief Gets all admin users
     * @return Vector of pointers to admin users
     */
    std::vector<Admin*> getAllAdmins() const;

    /**
     * @brief Gets all student users
     * @return Vector of pointers to student users
     */
    std::vector<Student*> getAllStudents() const;
};

#endif // USER_MANAGER_H
