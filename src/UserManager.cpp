//
// Created by jasmine nwajei on 23/04/2025.
//

#include "../include/UserManager.h"
#include <algorithm>

UserManager::UserManager() {
}

UserManager::~UserManager() {
    // Clean up all user objects
    for (auto user : users) {
        delete user;
    }
    users.clear();
}

User* UserManager::authenticate(const std::string& userId, const std::string& password) const {
    for (auto user : users) {
        if (user->getUserID() == userId && user->authenticate(password)) {
            return user;
        }
    }

    return nullptr; // Authentication failed
}

Admin* UserManager::registerAdmin(const std::string& id, const std::string& name,
                                const std::string& password, const std::string& department) {
    // Check if user ID already exists
    if (getUserById(id) != nullptr) {
        return nullptr; // User ID already exists
    }

    // Create new admin user
    Admin* admin = new Admin(id, name, password, department);
    users.push_back(admin);

    return admin;
}

Student* UserManager::registerStudent(const std::string& id, const std::string& name,
                                    const std::string& password, const std::string& studentNumber,
                                    const std::string& course) {
    // Check if user ID already exists
    if (getUserById(id) != nullptr) {
        return nullptr; // User ID already exists
    }

    // Create new student user
    Student* student = new Student(id, name, password, studentNumber, course);
    users.push_back(student);

    return student;
}

User* UserManager::getUserById(const std::string& userId) const {
    for (auto user : users) {
        if (user->getUserID() == userId) {
            return user;
        }
    }

    return nullptr; // User not found
}

std::vector<Admin*> UserManager::getAllAdmins() const {
    std::vector<Admin*> admins;

    for (auto user : users) {
        Admin* admin = dynamic_cast<Admin*>(user);
        if (admin) {
            admins.push_back(admin);
        }
    }

    return admins;
}

std::vector<Student*> UserManager::getAllStudents() const {
    std::vector<Student*> students;

    for (auto user : users) {
        Student* student = dynamic_cast<Student*>(user);
        if (student) {
            students.push_back(student);
        }
    }

    return students;
}