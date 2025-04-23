

#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <vector>
#include <string>
#include "../include/Admin.h"
#include "../include/GlobalVariables.h"

// Forward declarations
class Module;
class Student;
class Lecturer;
class Room;
class SessionType;
class TimetableManager;

/**
 * @class Admin
 * @brief Administrator user with system management capabilities
 *
 * The Admin class provides functionality for managing modules, student groups,
 * sessions, registering students and lecturers, and managing timetables.
 */
class Admin : public User {
private:
    std::string department;

public:
    /**
     * @brief Constructor for Admin class
     * @param id Admin ID
     * @param name Admin's name
     * @param pwd Admin's password
     * @param dept Admin's department
     */
    Admin(const std::string& id, const std::string& name, const std::string& pwd, const std::string& dept);

    /**
     * @brief Gets admin details including department
     * @return String containing admin information
     */
    std::string getUserDetails() const override;

    /**
     * @brief Gets the admin's department
     * @return Department string
     */
    std::string getDepartment() const;

    /**
     * @brief Creates a new module
     * @param moduleCode Unique code for the module
     * @param title Module title
     * @param description Module description
     * @return Pointer to the created module or nullptr if creation failed
     */
    Module* createModule(const std::string& moduleCode, const std::string& title, const std::string& description);

    /**
     * @brief Creates a student group
     * @param groupID Group identifier
     * @param groupName Name of the group
     * @return True if creation successful, false otherwise
     */
    bool createStudentGroup(const std::string& groupID, const std::string& groupName);

    /**
     * @brief Defines a new session type
     * @param typeID Unique identifier for session type
     * @param typeName Name of the session type
     * @return True if creation successful, false otherwise
     */
    bool defineSessionType(const std::string& typeID, const std::string& typeName);

    /**
     * @brief Registers a new student
     * @param id Student ID
     * @param name Student's name
     * @param pwd Student's password
     * @param studentNumber Student's registration number
     * @param course Student's course
     * @return Pointer to the created student or nullptr if registration failed
     */
    Student* registerStudent(const std::string& id, const std::string& name, const std::string& pwd,
                           const std::string& studentNumber, const std::string& course);

    /**
     * @brief Assigns a student to a group
     * @param studentID ID of the student
     * @param groupID ID of the group
     * @return True if assignment successful, false otherwise
     */
    bool assignStudentToGroup(const std::string& studentID, const std::string& groupID);

    /**
     * @brief Registers a new lecturer
     * @param id Lecturer ID
     * @param name Lecturer's name
     * @param department Lecturer's department
     * @return True if registration successful, false otherwise
     */
    bool registerLecturer(const std::string& id, const std::string& name, const std::string& department);

    /**
     * @brief Assigns a lecturer to a module
     * @param lecturerID ID of the lecturer
     * @param moduleCode Code of the module
     * @return True if assignment successful, false otherwise
     */
    bool assignLecturerToModule(const std::string& lecturerID, const std::string& moduleCode);

    /**
     * @brief Adds a new room
     * @param roomID Room identifier
     * @param location Room location
     * @param capacity Room capacity
     * @return True if room added successfully, false otherwise
     */
    bool addRoom(const std::string& roomID, const std::string& location, int capacity);

    /**
     * @brief Creates a timetable entry
     * @param timetableManager Reference to the timetable manager
     * @param week Week number
     * @param moduleCode Module code
     * @param lecturerID Lecturer ID
     * @param roomID Room ID
     * @param groupID Student group ID
     * @param sessionTypeID Session type ID
     * @param day Day of the week
     * @param startTime Start time
     * @param endTime End time
     * @return True if timetable entry created successfully, false otherwise
     */
    bool createTimetableEntry(TimetableManager& timetableManager, int week,
                             const std::string& moduleCode, const std::string& lecturerID,
                             const std::string& roomID, const std::string& groupID,
                             const std::string& sessionTypeID, const std::string& day,
                             const std::string& startTime, const std::string& endTime);

    /**
     * @brief Checks for timetable conflicts
     * @param timetableManager Reference to the timetable manager
     * @return True if conflicts exist, false otherwise
     */
    bool checkForConflicts(TimetableManager& timetableManager);
};


#endif // ADMIN_H