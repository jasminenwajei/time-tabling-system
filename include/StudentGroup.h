

#ifndef STUDENT_GROUP_H
#define STUDENT_GROUP_H

#include <string>
#include <vector>
#include "Student.h"

/**
 * @class StudentGroup
 * @brief Represents a group of students in the timetabling system
 *
 * The StudentGroup class manages student groups, allowing students
 * to be added or removed from groups.
 */
class StudentGroup {
private:
    std::string groupID;
    std::string groupName;
    std::vector<Student*> students;

public:
    /**
     * @brief Constructor for StudentGroup class
     * @param id Unique group identifier
     * @param name Group name
     */
    StudentGroup(const std::string& id, const std::string& name);

    /**
     * @brief Gets the group ID
     * @return Group ID string
     */
    std::string getGroupID() const;

    /**
     * @brief Gets the group name
     * @return Group name string
     */
    std::string getGroupName() const;

    /**
     * @brief Gets all students in the group
     * @return Vector of pointers to students
     */
    const std::vector<Student*>& getStudents() const;

    /**
     * @brief Adds a student to the group
     * @param student Pointer to the student to add
     * @return True if student was added successfully, false if already in group
     */
    bool addStudent(Student* student);

    /**
     * @brief Removes a student from the group
     * @param studentID ID of the student to remove
     * @return True if student was removed, false if not found
     */
    bool removeStudent(const std::string& studentID);

    /**
     * @brief Checks if a student is in the group
     * @param studentID ID of the student to check
     * @return True if student is in the group, false otherwise
     */
    bool hasStudent(const std::string& studentID) const;

    /**
     * @brief Gets detailed group information
     * @return String containing group details
     */
    std::string getDetails() const;
};

#endif // STUDENT_GROUP_H