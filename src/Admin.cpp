
#include "../include/Admin.h"
#include "../include/Module.h"
#include "../include/Student.h"
#include "../include/Lecturer.h"
#include "../include/Room.h"
#include "../include/SessionType.h"
#include "../include/StudentGroup.h"
#include "../include/TimeSlot.h"
#include "../include/TimetableManager.h"
#include <iostream>

// Global collections for simplicity in this demonstration
extern std::vector<Module*> g_modules;
extern std::vector<Student*> g_students;
extern std::vector<Lecturer*> g_lecturers;
extern std::vector<Room*> g_rooms;
extern std::vector<SessionType*> g_sessionTypes;
extern std::vector<StudentGroup*> g_studentGroups;

Admin::Admin(const std::string& id, const std::string& name, const std::string& pwd, const std::string& dept)
    : User(id, name, pwd), department(dept) {
}

std::string Admin::getUserDetails() const {
    return User::getUserDetails() + ", Department: " + department;
}

std::string Admin::getDepartment() const {
    return department;
}

Module* Admin::createModule(const std::string& moduleCode, const std::string& title, const std::string& description) {
    // Check if module code already exists
    for (auto& module : g_modules) {
        if (module->getModuleCode() == moduleCode) {
            std::cout << "Module with code " << moduleCode << " already exists." << std::endl;
            return nullptr;
        }
    }

    // Create new module and add to collection
    Module* newModule = new Module(moduleCode, title, description);
    g_modules.push_back(newModule);
    std::cout << "Module created: " << newModule->getDetails() << std::endl;
    return newModule;
}

bool Admin::createStudentGroup(const std::string& groupID, const std::string& groupName) {
    // Check if group ID already exists
    for (auto& group : g_studentGroups) {
        if (group->getGroupID() == groupID) {
            std::cout << "Student group with ID " << groupID << " already exists." << std::endl;
            return false;
        }
    }

    // Create new student group and add to collection
    StudentGroup* newGroup = new StudentGroup(groupID, groupName);
    g_studentGroups.push_back(newGroup);
    std::cout << "Student group created: " << groupName << " (" << groupID << ")" << std::endl;
    return true;
}

bool Admin::defineSessionType(const std::string& typeID, const std::string& typeName) {
    // Check if session type ID already exists
    for (auto& type : g_sessionTypes) {
        if (type->getTypeID() == typeID) {
            std::cout << "Session type with ID " << typeID << " already exists." << std::endl;
            return false;
        }
    }

    // Create new session type and add to collection
    SessionType* newType = new SessionType(typeID, typeName);
    g_sessionTypes.push_back(newType);
    std::cout << "Session type created: " << typeName << " (" << typeID << ")" << std::endl;
    return true;
}

Student* Admin::registerStudent(const std::string& id, const std::string& name, const std::string& pwd,
                              const std::string& studentNumber, const std::string& course) {
    // Check if student ID already exists
    for (auto& student : g_students) {
        if (student->getUserID() == id || student->getStudentNumber() == studentNumber) {
            std::cout << "Student with ID " << id << " or number " << studentNumber << " already exists." << std::endl;
            return nullptr;
        }
    }

    // Create new student and add to collection
    Student* newStudent = new Student(id, name, pwd, studentNumber, course);
    g_students.push_back(newStudent);
    std::cout << "Student registered: " << newStudent->getUserDetails() << std::endl;
    return newStudent;
}

bool Admin::assignStudentToGroup(const std::string& studentID, const std::string& groupID) {
    // Find student
    Student* student = nullptr;
    for (auto& s : g_students) {
        if (s->getUserID() == studentID) {
            student = s;
            break;
        }
    }

    if (!student) {
        std::cout << "Student with ID " << studentID << " not found." << std::endl;
        return false;
    }

    // Find group
    StudentGroup* group = nullptr;
    for (auto& g : g_studentGroups) {
        if (g->getGroupID() == groupID) {
            group = g;
            break;
        }
    }

    if (!group) {
        std::cout << "Student group with ID " << groupID << " not found." << std::endl;
        return false;
    }

    // Assign student to group
    group->addStudent(student);
    std::cout << "Student " << student->getName() << " assigned to group " << group->getGroupName() << std::endl;
    return true;
}

bool Admin::registerLecturer(const std::string& id, const std::string& name, const std::string& department) {
    // Check if lecturer ID already exists
    for (auto& lecturer : g_lecturers) {
        if (lecturer->getLecturerID() == id) {
            std::cout << "Lecturer with ID " << id << " already exists." << std::endl;
            return false;
        }
    }

    // Create new lecturer and add to collection
    Lecturer* newLecturer = new Lecturer(id, name, department);
    g_lecturers.push_back(newLecturer);
    std::cout << "Lecturer registered: " << newLecturer->getName() << " (" << department << ")" << std::endl;
    return true;
}

bool Admin::assignLecturerToModule(const std::string& lecturerID, const std::string& moduleCode) {
    // Find lecturer
    Lecturer* lecturer = nullptr;
    for (auto& l : g_lecturers) {
        if (l->getLecturerID() == lecturerID) {
            lecturer = l;
            break;
        }
    }

    if (!lecturer) {
        std::cout << "Lecturer with ID " << lecturerID << " not found." << std::endl;
        return false;
    }

    // Find module
    Module* module = nullptr;
    for (auto& m : g_modules) {
        if (m->getModuleCode() == moduleCode) {
            module = m;
            break;
        }
    }

    if (!module) {
        std::cout << "Module with code " << moduleCode << " not found." << std::endl;
        return false;
    }

    // Assign lecturer to module
    lecturer->assignModule(module);
    std::cout << "Lecturer " << lecturer->getName() << " assigned to module " << module->getTitle() << std::endl;
    return true;
}

bool Admin::addRoom(const std::string& roomID, const std::string& location, int capacity) {
    // Check if room ID already exists
    for (auto& room : g_rooms) {
        if (room->getRoomID() == roomID) {
            std::cout << "Room with ID " << roomID << " already exists." << std::endl;
            return false;
        }
    }

    // Create new room and add to collection
    Room* newRoom = new Room(roomID, location, capacity);
    g_rooms.push_back(newRoom);
    std::cout << "Room added: " << newRoom->getDetails() << std::endl;
    return true;
}

bool Admin::createTimetableEntry(TimetableManager& timetableManager, int week,
                                const std::string& moduleCode, const std::string& lecturerID,
                                const std::string& roomID, const std::string& groupID,
                                const std::string& sessionTypeID, const std::string& day,
                                const std::string& startTime, const std::string& endTime) {
    // Find module
    Module* module = nullptr;
    for (auto& m : g_modules) {
        if (m->getModuleCode() == moduleCode) {
            module = m;
            break;
        }
    }

    if (!module) {
        std::cout << "Module with code " << moduleCode << " not found." << std::endl;
        return false;
    }

    // Find lecturer
    Lecturer* lecturer = nullptr;
    for (auto& l : g_lecturers) {
        if (l->getLecturerID() == lecturerID) {
            lecturer = l;
            break;
        }
    }

    if (!lecturer) {
        std::cout << "Lecturer with ID " << lecturerID << " not found." << std::endl;
        return false;
    }

    // Find room
    Room* room = nullptr;
    for (auto& r : g_rooms) {
        if (r->getRoomID() == roomID) {
            room = r;
            break;
        }
    }

    if (!room) {
        std::cout << "Room with ID " << roomID << " not found." << std::endl;
        return false;
    }

    // Find student group
    StudentGroup* group = nullptr;
    for (auto& g : g_studentGroups) {
        if (g->getGroupID() == groupID) {
            group = g;
            break;
        }
    }

    if (!group) {
        std::cout << "Student group with ID " << groupID << " not found." << std::endl;
        return false;
    }

    // Find session type
    SessionType* sessionType = nullptr;
    for (auto& s : g_sessionTypes) {
        if (s->getTypeID() == sessionTypeID) {
            sessionType = s;
            break;
        }
    }

    if (!sessionType) {
        std::cout << "Session type with ID " << sessionTypeID << " not found." << std::endl;
        return false;
    }

    // Create time slot
    TimeSlot* timeSlot = new TimeSlot(day, startTime, endTime);

    // Create timetable entry
    TimetableEntry* entry = timetableManager.createEntry(week, module, lecturer, room, group, sessionType, timeSlot);

    if (entry) {
        std::cout << "Timetable entry created: " << entry->getEntryDetails() << std::endl;
        return true;
    } else {
        std::cout << "Failed to create timetable entry." << std::endl;
        delete timeSlot; // Clean up if entry creation failed
        return false;
    }
}

bool Admin::checkForConflicts(TimetableManager& timetableManager) {
    timetableManager.checkForConflicts();

    if (timetableManager.hasConflicts()) {
        auto conflicts = timetableManager.getConflicts();
        std::cout << "Found " << conflicts.size() << " conflicts:" << std::endl;

        for (const auto& conflict : conflicts) {
            std::cout << "Conflict between:" << std::endl;
            std::cout << "  1. " << conflict.first->getEntryDetails() << std::endl;
            std::cout << "  2. " << conflict.second->getEntryDetails() << std::endl;
        }
        return true;
    }

    std::cout << "No timetable conflicts found." << std::endl;
    return false;
}