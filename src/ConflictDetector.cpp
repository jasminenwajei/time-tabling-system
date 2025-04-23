//
// Created by jasmine nwajei on 23/04/2025.
//
#include "../include/ConflictDetector.h"
#include <algorithm>
#include <sstream>

ConflictDetector::ConflictDetector() {
    conflictTypes = {"Room Double-booking", "Lecturer Time Conflict", "Student Group Time Conflict"};
}

void ConflictDetector::detectConflicts(const std::vector<TimetableEntry*>& entries) {
    conflicts.clear();

    // Check every pair of entries for conflicts
    for (size_t i = 0; i < entries.size(); ++i) {
        for (size_t j = i + 1; j < entries.size(); ++j) {
            if (entries[i]->checkConflict(*entries[j])) {
                conflicts.push_back({entries[i], entries[j]});
            }
        }
    }
}

bool ConflictDetector::hasConflicts() const {
    return !conflicts.empty();
}

std::vector<std::pair<TimetableEntry*, TimetableEntry*>> ConflictDetector::getConflicts() const {
    return conflicts;
}

std::string ConflictDetector::suggestResolution(const std::pair<TimetableEntry*, TimetableEntry*>& conflict) const {
    TimetableEntry* entry1 = conflict.first;
    TimetableEntry* entry2 = conflict.second;

    std::stringstream ss;
    ss << "Conflict found between:\n";
    ss << "1. " << entry1->getEntryDetails() << "\n";
    ss << "2. " << entry2->getEntryDetails() << "\n\n";

    // Identify conflict type and suggest resolution
    if (entry1->getRoom()->getRoomID() == entry2->getRoom()->getRoomID()) {
        ss << "Room Double-booking: Consider using a different room for one of the sessions.\n";
        ss << "  - Suggestion: Move session 2 to a different room.\n";
    }

    if (entry1->getLecturer()->getLecturerID() == entry2->getLecturer()->getLecturerID()) {
        ss << "Lecturer Time Conflict: Consider rescheduling one session to a different time slot.\n";
        ss << "  - Suggestion: Reschedule session 2 to a different day or time.\n";
    }

    if (entry1->getStudentGroup()->getGroupID() == entry2->getStudentGroup()->getGroupID()) {
        ss << "Student Group Time Conflict: Students cannot attend two sessions simultaneously.\n";
        ss << "  - Suggestion: Reschedule one of the sessions to avoid time overlap.\n";
    }

    return ss.str();
}