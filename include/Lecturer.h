

#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include <vector>
#include <map>
#include "Module.h"
#include "TimeSlot.h"

/**
 * @class Lecturer
 * @brief Represents a lecturer in the timetabling system
 *
 * The Lecturer class manages information about lecturers and their
 * assigned modules and availability.
 */
class Lecturer {
private:
    std::string lecturerID;
    std::string name;
    std::string department;
    std::vector<Module*> assignedModules;
    std::map<std::string, std::vector<TimeSlot*>> schedule; // Day -> List of occupied time slots

public:
    /**
     * @brief Constructor for Lecturer class
     * @param id Unique lecturer identifier
     * @param lecturerName Lecturer's name
     * @param dept Lecturer's department
     */
    Lecturer(const std::string& id, const std::string& lecturerName, const std::string& dept);

    /**
     * @brief Gets the lecturer ID
     * @return Lecturer ID string
     */
    std::string getLecturerID() const;

    /**
     * @brief Gets the lecturer's name
     * @return Lecturer name string
     */
    std::string getName() const;

    /**
     * @brief Gets the lecturer's department
     * @return Department string
     */
    std::string getDepartment() const;

    /**
     * @brief Gets all modules assigned to the lecturer
     * @return Vector of pointers to assigned modules
     */
    const std::vector<Module*>& getAssignedModules() const;

    /**
     * @brief Assigns a module to the lecturer
     * @param module Pointer to the module to assign
     * @return True if module was assigned, false if already assigned
     */
    bool assignModule(Module* module);

    /**
     * @brief Removes a module from the lecturer's assignments
     * @param moduleCode Code of the module to remove
     * @return True if module was removed, false if not found
     */
    bool removeModule(const std::string& moduleCode);

    /**
     * @brief Checks if lecturer is available at a specific time
     * @param day Day of the week
     * @param timeSlot Time slot to check
     * @return True if lecturer is available, false if busy
     */
    bool isAvailable(const TimeSlot& timeSlot) const;

    /**
     * @brief Adds a time slot to the lecturer's schedule
     * @param timeSlot Time slot to add
     * @return True if time slot was added, false if conflict exists
     */
    bool addToSchedule(TimeSlot* timeSlot);

    /**
     * @brief Gets detailed lecturer information
     * @return String containing lecturer details
     */
    std::string getDetails() const;
};

#endif // LECTURER_H