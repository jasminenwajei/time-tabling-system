

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include <string>
#include <vector>

// Forward declarations
class TimetableManager;
class TimetableEntry;

/**
 * @class Student
 * @brief Student user with timetable viewing capabilities
 *
 * The Student class provides functionality for viewing and exporting timetables.
 */
class Student : public User {
private:
    std::string studentNumber;
    std::string course;

public:
    /**
     * @brief Constructor for Student class
     * @param id Student ID
     * @param name Student's name
     * @param pwd Student's password
     * @param studentNum Student's registration number
     * @param courseName Student's course
     */
    Student(const std::string& id, const std::string& name, const std::string& pwd,
            const std::string& studentNum, const std::string& courseName);

    /**
     * @brief Gets student details including student number and course
     * @return String containing student information
     */
    std::string getUserDetails() const override;

    /**
     * @brief Gets the student number
     * @return Student number string
     */
    std::string getStudentNumber() const;

    /**
     * @brief Gets the student's course
     * @return Course string
     */
    std::string getCourse() const;

    /**
     * @brief Views the student's timetable for a specific week
     * @param timetableManager Reference to the timetable manager
     * @param week Week number (optional, -1 for all weeks)
     * @return Vector of timetable entries for the student
     */
    std::vector<TimetableEntry*> viewTimetable(const TimetableManager& timetableManager,
                                              int week = -1) const;

    /**
     * @brief Searches the student's timetable
     * @param timetableManager Reference to the timetable manager
     * @param week Week number (optional)
     * @param moduleCode Module code (optional)
     * @param roomID Room ID (optional)
     * @param lecturerID Lecturer ID (optional)
     * @return Vector of timetable entries matching the search criteria
     */
    std::vector<TimetableEntry*> searchTimetable(const TimetableManager& timetableManager,
                                                int week = -1,
                                                const std::string& moduleCode = "",
                                                const std::string& roomID = "",
                                                const std::string& lecturerID = "") const;

    /**
     * @brief Exports the student's timetable to a CSV file
     * @param timetableManager Reference to the timetable manager
     * @param filename Name of the output file
     * @param week Week number (optional, -1 for all weeks)
     * @return True if export successful, false otherwise
     */
    bool exportTimetable(const TimetableManager& timetableManager,
                         const std::string& filename,
                         int week = -1) const;
};

#endif // STUDENT_H