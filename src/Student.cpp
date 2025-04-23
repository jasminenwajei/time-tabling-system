//
// Created by jasmine nwajei on 23/04/2025.
//

#include "../include/Student.h"
#include "../include/TimetableManager.h"
#include "../include/TimetableEntry.h"
#include "../include/StudentGroup.h"
#include <iostream>
#include <fstream>

// Global collections for simplicity
extern std::vector<StudentGroup*> g_studentGroups;

Student::Student(const std::string& id, const std::string& name, const std::string& pwd,
                 const std::string& studentNum, const std::string& courseName)
    : User(id, name, pwd), studentNumber(studentNum), course(courseName) {
}

std::string Student::getUserDetails() const {
    return User::getUserDetails() + ", Student Number: " + studentNumber + ", Course: " + course;
}

std::string Student::getStudentNumber() const {
    return studentNumber;
}

std::string Student::getCourse() const {
    return course;
}

std::vector<TimetableEntry*> Student::viewTimetable(const TimetableManager& timetableManager, int week) const {
    std::vector<TimetableEntry*> studentTimetable;

    // Find all groups this student belongs to
    std::vector<std::string> groupIDs;
    for (const auto& group : g_studentGroups) {
        if (group->hasStudent(getUserID())) {
            groupIDs.push_back(group->getGroupID());
        }
    }

    // If student isn't in any groups, return empty timetable
    if (groupIDs.empty()) {
        std::cout << "Student does not belong to any groups." << std::endl;
        return studentTimetable;
    }

    // Collect timetable entries for all groups the student belongs to
    for (const auto& groupID : groupIDs) {
        auto groupTimetable = timetableManager.getTimetableForGroup(groupID, week);
        studentTimetable.insert(studentTimetable.end(), groupTimetable.begin(), groupTimetable.end());
    }

    // Display timetable in console
    std::cout << "\n==== Timetable for " << getName() << " (" << studentNumber << ") ====\n";
    if (week != -1) {
        std::cout << "Week: " << week << "\n";
    }

    if (studentTimetable.empty()) {
        std::cout << "No sessions scheduled." << std::endl;
    } else {
        for (const auto& entry : studentTimetable) {
            std::cout << entry->getEntryDetails() << std::endl;
        }
    }

    return studentTimetable;
}

std::vector<TimetableEntry*> Student::searchTimetable(const TimetableManager& timetableManager,
                                                    int week,
                                                    const std::string& moduleCode,
                                                    const std::string& roomID,
                                                    const std::string& lecturerID) const {
    // Get the student's timetable first
    auto studentTimetable = viewTimetable(timetableManager, -1); // Get all weeks

    // Apply filters
    std::vector<TimetableEntry*> filteredTimetable;
    for (const auto& entry : studentTimetable) {
        bool matchesWeek = (week == -1) || (entry->getWeekNumber() == week);
        bool matchesModule = moduleCode.empty() || (entry->getModule()->getModuleCode() == moduleCode);
        bool matchesRoom = roomID.empty() || (entry->getRoom()->getRoomID() == roomID);
        bool matchesLecturer = lecturerID.empty() || (entry->getLecturer()->getLecturerID() == lecturerID);

        if (matchesWeek && matchesModule && matchesRoom && matchesLecturer) {
            filteredTimetable.push_back(entry);
        }
    }

    // Display search results in console
    std::cout << "\n==== Search Results for " << getName() << " ====\n";

    if (filteredTimetable.empty()) {
        std::cout << "No matching sessions found." << std::endl;
    } else {
        std::cout << "Found " << filteredTimetable.size() << " matching sessions:" << std::endl;
        for (const auto& entry : filteredTimetable) {
            std::cout << entry->getEntryDetails() << std::endl;
        }
    }

    return filteredTimetable;
}

bool Student::exportTimetable(const TimetableManager& timetableManager, const std::string& filename, int week) const {
    // Get the student's timetable
    auto studentTimetable = viewTimetable(timetableManager, week);

    // Check if we have anything to export
    if (studentTimetable.empty()) {
        std::cout << "No timetable data to export." << std::endl;
        return false;
    }

    // Open the file for writing
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file for writing: " << filename << std::endl;
        return false;
    }

    // Write CSV header
    file << "Week,Day,Start Time,End Time,Module,Module Code,Lecturer,Room,Session Type\n";

    // Write timetable entries
    for (const auto& entry : studentTimetable) {
        file << entry->getWeekNumber() << ","
             << entry->getTimeSlot()->getDay() << ","
             << entry->getTimeSlot()->getStartTime() << ","
             << entry->getTimeSlot()->getEndTime() << ","
             << entry->getModule()->getTitle() << ","
             << entry->getModule()->getModuleCode() << ","
             << entry->getLecturer()->getName() << ","
             << entry->getRoom()->getRoomID() << ","
             << entry->getSessionType()->getTypeName() << "\n";
    }

    file.close();
    std::cout << "Timetable exported to " << filename << " successfully." << std::endl;
    return true;
}