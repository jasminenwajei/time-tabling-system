
#include "../include/StudentGroup.h"
#include <algorithm>
#include <sstream>

StudentGroup::StudentGroup(const std::string& id, const std::string& name)
    : groupID(id), groupName(name) {
}

std::string StudentGroup::getGroupID() const {
    return groupID;
}

std::string StudentGroup::getGroupName() const {
    return groupName;
}

const std::vector<Student*>& StudentGroup::getStudents() const {
    return students;
}

bool StudentGroup::addStudent(Student* student) {
    if (!student) {
        return false;
    }

    if (!hasStudent(student->getUserID())) {
        students.push_back(student);
        return true;
    }

    return false; // Student already in group
}

bool StudentGroup::removeStudent(const std::string& studentID) {
    auto it = std::find_if(students.begin(), students.end(),
                           [&studentID](const Student* s) { return s->getUserID() == studentID; });

    if (it != students.end()) {
        students.erase(it);
        return true;
    }

    return false; // Student not found
}

bool StudentGroup::hasStudent(const std::string& studentID) const {
    return std::any_of(students.begin(), students.end(),
                      [&studentID](const Student* s) { return s->getUserID() == studentID; });
}

std::string StudentGroup::getDetails() const {
    std::stringstream ss;
    ss << "Group ID: " << groupID << ", Name: " << groupName;
    ss << ", Students: " << students.size();

    return ss.str();
}