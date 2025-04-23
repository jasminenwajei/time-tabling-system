

#ifndef CONFLICT_DETECTOR_H
#define CONFLICT_DETECTOR_H

#include <vector>
#include <string>
#include <utility>
#include "TimetableEntry.h"

/**
 * @class ConflictDetector
 * @brief Detects conflicts in the timetabling system
 *
 * The ConflictDetector class analyzes timetable entries to find scheduling
 * conflicts such as double-booked rooms, lecturer time conflicts, and
 * student group time conflicts.
 */
class ConflictDetector {
private:
    std::vector<std::string> conflictTypes;
    std::vector<std::pair<TimetableEntry*, TimetableEntry*>> conflicts;

public:
    /**
     * @brief Constructor for ConflictDetector class
     */
    ConflictDetector();

    /**
     * @brief Detects conflicts in a set of timetable entries
     * @param entries Vector of pointers to timetable entries to check
     */
    void detectConflicts(const std::vector<TimetableEntry*>& entries);

    /**
     * @brief Checks if any conflicts were detected
     * @return True if conflicts exist, false otherwise
     */
    bool hasConflicts() const;

    /**
     * @brief Gets all detected conflicts
     * @return Vector of pairs of conflicting timetable entries
     */
    std::vector<std::pair<TimetableEntry*, TimetableEntry*>> getConflicts() const;

    /**
     * @brief Suggests a resolution for a conflict
     * @param conflict Pair of conflicting timetable entries
     * @return String containing suggested resolution
     */
    std::string suggestResolution(const std::pair<TimetableEntry*, TimetableEntry*>& conflict) const;
};

#endif // CONFLICT_DETECTOR_H