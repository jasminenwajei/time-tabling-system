

#ifndef TIMETABLE_MANAGER_H
#define TIMETABLE_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "TimetableEntry.h"
#include "ConflictDetector.h"
#include "Module.h"
#include "Lecturer.h"
#include "Room.h"
#include "StudentGroup.h"
#include "SessionType.h"
#include "TimeSlot.h"

/**
 * @class TimetableManager
 * @brief Manages timetable entries and provides search and export functionality
 *
 * The TimetableManager class is responsible for creating, storing, and
 * retrieving timetable entries, as well as checking for conflicts and
 * exporting timetable data.
 */
class TimetableManager {
private:
    std::string academicYear;
    std::string semester;
    std::vector<TimetableEntry*> timetableEntries;
    ConflictDetector conflictDetector;

    // Helper function to generate unique entry IDs
    std::string generateEntryID() const;

public:
    /**
     * @brief Constructor for TimetableManager class
     * @param year Academic year (e.g., "2024-2025")
     * @param sem Semester (e.g., "Fall", "Spring")
     */
    TimetableManager(const std::string& year, const std::string& sem);

    /**
     * @brief Destructor to clean up owned timetable entries
     */
    ~TimetableManager();

    /**
     * @brief Gets the academic year
     * @return Academic year string
     */
    std::string getAcademicYear() const;

    /**
     * @brief Gets the semester
     * @return Semester string
     */
    std::string getSemester() const;

    /**
     * @brief Creates a new timetable entry
     * @param week Week number
     * @param mod Module pointer
     * @param lec Lecturer pointer
     * @param rm Room pointer
     * @param group Student group pointer
     * @param session Session type pointer
     * @param time Time slot pointer
     * @return Pointer to created timetable entry, or nullptr if creation failed
     */
    TimetableEntry* createEntry(int week, Module* mod, Lecturer* lec,
                               Room* rm, StudentGroup* group,
                               SessionType* session, TimeSlot* time);

    /**
     * @brief Searches for timetable entries matching criteria
     * @param week Week number (-1 for all weeks)
     * @param moduleCode Module code (empty for all modules)
     * @param roomID Room ID (empty for all rooms)
     * @param lecturerID Lecturer ID (empty for all lecturers)
     * @return Vector of pointers to matching timetable entries
     */
    std::vector<TimetableEntry*> searchTimetable(int week = -1,
                                                const std::string& moduleCode = "",
                                                const std::string& roomID = "",
                                                const std::string& lecturerID = "") const;

    /**
     * @brief Exports timetable data to a CSV file
     * @param filename Name of the output file
     * @return True if export successful, false otherwise
     */
    bool exportToCSV(const std::string& filename) const;

    /**
     * @brief Gets all timetable entries for a specific student group
     * @param groupID Student group ID
     * @param week Week number (-1 for all weeks)
     * @return Vector of pointers to matching timetable entries
     */
    std::vector<TimetableEntry*> getTimetableForGroup(const std::string& groupID, int week = -1) const;

    /**
     * @brief Gets all timetable entries for a specific lecturer
     * @param lecturerID Lecturer ID
     * @param week Week number (-1 for all weeks)
     * @return Vector of pointers to matching timetable entries
     */
    std::vector<TimetableEntry*> getTimetableForLecturer(const std::string& lecturerID, int week = -1) const;

    /**
     * @brief Gets all timetable entries for a specific room
     * @param roomID Room ID
     * @param week Week number (-1 for all weeks)
     * @return Vector of pointers to matching timetable entries
     */
    std::vector<TimetableEntry*> getTimetableForRoom(const std::string& roomID, int week = -1) const;

    /**
     * @brief Checks for conflicts in the timetable
     */
    void checkForConflicts();

    /**
     * @brief Checks if any conflicts exist in the timetable
     * @return True if conflicts exist, false otherwise
     */
    bool hasConflicts() const;

    /**
     * @brief Gets all conflicts in the timetable
     * @return Vector of pairs of conflicting timetable entries
     */
    std::vector<std::pair<TimetableEntry*, TimetableEntry*>> getConflicts() const;

    /**
     * @brief Deletes a timetable entry
     * @param entryID ID of the entry to delete
     * @return True if entry was deleted, false if not found
     */
    bool deleteEntry(const std::string& entryID);

    /**
     * @brief Gets all timetable entries
     * @return Vector of pointers to all timetable entries
     */
    const std::vector<TimetableEntry*>& getAllEntries() const;
};

#endif // TIMETABLE_MANAGER_H