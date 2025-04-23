
#ifndef TIMETABLE_ENTRY_H
#define TIMETABLE_ENTRY_H

#include <string>
#include "Module.h"
#include "Lecturer.h"
#include "Room.h"
#include "StudentGroup.h"
#include "SessionType.h"
#include "TimeSlot.h"

/**
 * @class TimetableEntry
 * @brief Represents a scheduled session in the timetabling system
 *
 * The TimetableEntry class combines all necessary components to define
 * a scheduled session: module, lecturer, room, student group, session type,
 * and time slot.
 */
class TimetableEntry {
private:
    std::string entryID;
    int weekNumber;
    Module* module;
    Lecturer* lecturer;
    Room* room;
    StudentGroup* studentGroup;
    SessionType* sessionType;
    TimeSlot* timeSlot;

public:
    /**
     * @brief Constructor for TimetableEntry class
     * @param id Unique entry identifier
     * @param week Week number (1-53)
     * @param mod Pointer to module
     * @param lec Pointer to lecturer
     * @param rm Pointer to room
     * @param group Pointer to student group
     * @param session Pointer to session type
     * @param time Pointer to time slot
     */
    TimetableEntry(const std::string& id, int week, Module* mod, Lecturer* lec,
                  Room* rm, StudentGroup* group, SessionType* session, TimeSlot* time);

    /**
     * @brief Destructor to clean up owned time slot
     */
    ~TimetableEntry();

    /**
     * @brief Gets the entry ID
     * @return Entry ID string
     */
    std::string getEntryID() const;

    /**
     * @brief Gets the week number
     * @return Week number as integer
     */
    int getWeekNumber() const;

    /**
     * @brief Gets the module
     * @return Pointer to module
     */
    Module* getModule() const;

    /**
     * @brief Gets the lecturer
     * @return Pointer to lecturer
     */
    Lecturer* getLecturer() const;

    /**
     * @brief Gets the room
     * @return Pointer to room
     */
    Room* getRoom() const;

    /**
     * @brief Gets the student group
     * @return Pointer to student group
     */
    StudentGroup* getStudentGroup() const;

    /**
     * @brief Gets the session type
     * @return Pointer to session type
     */
    SessionType* getSessionType() const;

    /**
     * @brief Gets the time slot
     * @return Pointer to time slot
     */
    TimeSlot* getTimeSlot() const;

    /**
     * @brief Gets detailed entry information
     * @return String containing timetable entry details
     */
    std::string getEntryDetails() const;

    /**
     * @brief Checks if this entry conflicts with another
     * @param other Other entry to check against
     * @return True if there is a conflict, false otherwise
     */
    bool checkConflict(const TimetableEntry& other) const;
};

#endif // TIMETABLE_ENTRY_H