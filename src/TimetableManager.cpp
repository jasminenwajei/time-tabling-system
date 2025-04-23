//
// Created by jasmine nwajei on 23/04/2025.
//

#include "../include/TimetableManager.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

TimetableManager::TimetableManager(const std::string& year, const std::string& sem)
    : academicYear(year), semester(sem) {
}

TimetableManager::~TimetableManager() {
    // Clean up all timetable entries
    for (auto entry : timetableEntries) {
        delete entry;
    }
    timetableEntries.clear();
}

std::string TimetableManager::getAcademicYear() const {
    return academicYear;
}

std::string TimetableManager::getSemester() const {
    return semester;
}

std::string TimetableManager::generateEntryID() const {
    // Generate a unique ID based on the current number of entries
    std::stringstream ss;
    ss << "TT" << std::setw(4) << std::setfill('0') << (timetableEntries.size() + 1);
    return ss.str();
}

TimetableEntry* TimetableManager::createEntry(int week, Module* mod, Lecturer* lec,
                                           Room* rm, StudentGroup* group,
                                           SessionType* session, TimeSlot* time) {
    // Validate input parameters
    if (!mod || !lec || !rm || !group || !session || !time) {
        return nullptr;
    }

    // Check if the week number is valid (1-53)
    if (week < 1 || week > 53) {
        return nullptr;
    }

    // Check if the lecturer is available at this time
    if (!lec->isAvailable(*time)) {
        return nullptr;
    }

    // Check if the room is available at this time
    if (!rm->isAvailable(*time)) {
        return nullptr;
    }

    // Generate a unique ID for the entry
    std::string entryID = generateEntryID();

    // Create the new entry
    TimetableEntry* newEntry = new TimetableEntry(entryID, week, mod, lec, rm, group, session, time);

    // Add to the collection
    timetableEntries.push_back(newEntry);

    // Check for conflicts (this should not find conflicts with the just-added entry
    // due to the availability checks above, but could find conflicts introduced by
    // changes elsewhere in the system)
    checkForConflicts();

    return newEntry;
}

std::vector<TimetableEntry*> TimetableManager::searchTimetable(int week,
                                                            const std::string& moduleCode,
                                                            const std::string& roomID,
                                                            const std::string& lecturerID) const {
    std::vector<TimetableEntry*> results;

    for (auto entry : timetableEntries) {
        bool matchesWeek = (week == -1) || (entry->getWeekNumber() == week);
        bool matchesModule = moduleCode.empty() || (entry->getModule()->getModuleCode() == moduleCode);
        bool matchesRoom = roomID.empty() || (entry->getRoom()->getRoomID() == roomID);
        bool matchesLecturer = lecturerID.empty() || (entry->getLecturer()->getLecturerID() == lecturerID);

        if (matchesWeek && matchesModule && matchesRoom && matchesLecturer) {
            results.push_back(entry);
        }
    }

    return results;
}

bool TimetableManager::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Write header
    file << "EntryID,Week,Module,ModuleCode,Lecturer,Room,StudentGroup,SessionType,Day,StartTime,EndTime\n";

    // Write data
    for (const auto& entry : timetableEntries) {
        file << entry->getEntryID() << ","
             << entry->getWeekNumber() << ","
             << entry->getModule()->getTitle() << ","
             << entry->getModule()->getModuleCode() << ","
             << entry->getLecturer()->getName() << ","
             << entry->getRoom()->getRoomID() << ","
             << entry->getStudentGroup()->getGroupName() << ","
             << entry->getSessionType()->getTypeName() << ","
             << entry->getTimeSlot()->getDay() << ","
             << entry->getTimeSlot()->getStartTime() << ","
             << entry->getTimeSlot()->getEndTime() << "\n";
    }

    file.close();
    return true;
}

std::vector<TimetableEntry*> TimetableManager::getTimetableForGroup(const std::string& groupID, int week) const {
    std::vector<TimetableEntry*> results;

    for (auto entry : timetableEntries) {
        bool matchesWeek = (week == -1) || (entry->getWeekNumber() == week);
        bool matchesGroup = entry->getStudentGroup()->getGroupID() == groupID;

        if (matchesWeek && matchesGroup) {
            results.push_back(entry);
        }
    }

    return results;
}

std::vector<TimetableEntry*> TimetableManager::getTimetableForLecturer(const std::string& lecturerID, int week) const {
    std::vector<TimetableEntry*> results;

    for (auto entry : timetableEntries) {
        bool matchesWeek = (week == -1) || (entry->getWeekNumber() == week);
        bool matchesLecturer = entry->getLecturer()->getLecturerID() == lecturerID;

        if (matchesWeek && matchesLecturer) {
            results.push_back(entry);
        }
    }

    return results;
}

std::vector<TimetableEntry*> TimetableManager::getTimetableForRoom(const std::string& roomID, int week) const {
    std::vector<TimetableEntry*> results;

    for (auto entry : timetableEntries) {
        bool matchesWeek = (week == -1) || (entry->getWeekNumber() == week);
        bool matchesRoom = entry->getRoom()->getRoomID() == roomID;

        if (matchesWeek && matchesRoom) {
            results.push_back(entry);
        }
    }

    return results;
}

void TimetableManager::checkForConflicts() {
    conflictDetector.detectConflicts(timetableEntries);
}

bool TimetableManager::hasConflicts() const {
    return conflictDetector.hasConflicts();
}

std::vector<std::pair<TimetableEntry*, TimetableEntry*>> TimetableManager::getConflicts() const {
    return conflictDetector.getConflicts();
}

bool TimetableManager::deleteEntry(const std::string& entryID) {
    auto it = std::find_if(timetableEntries.begin(), timetableEntries.end(),
                           [&entryID](const TimetableEntry* entry) {
                               return entry->getEntryID() == entryID;
                           });

    if (it != timetableEntries.end()) {
        delete *it;
        timetableEntries.erase(it);
        return true;
    }

    return false;
}

const std::vector<TimetableEntry*>& TimetableManager::getAllEntries() const {
    return timetableEntries;
}