

#include "../include/Lecturer.h"
#include <algorithm>
#include <sstream>

Lecturer::Lecturer(const std::string& id, const std::string& lecturerName, const std::string& dept)
    : lecturerID(id), name(lecturerName), department(dept) {
}

std::string Lecturer::getLecturerID() const {
    return lecturerID;
}

std::string Lecturer::getName() const {
    return name;
}

std::string Lecturer::getDepartment() const {
    return department;
}

const std::vector<Module*>& Lecturer::getAssignedModules() const {
    return assignedModules;
}

bool Lecturer::assignModule(Module* module) {
    if (!module) {
        return false;
    }

    // Check if module already assigned
    auto it = std::find_if(assignedModules.begin(), assignedModules.end(),
                       [module](const Module* m) { return m->getModuleCode() == module->getModuleCode(); });

    if (it == assignedModules.end()) {
        assignedModules.push_back(module);
        return true;
    }

    return false; // Module already assigned
}

bool Lecturer::removeModule(const std::string& moduleCode) {
    auto it = std::find_if(assignedModules.begin(), assignedModules.end(),
                       [&moduleCode](const Module* m) { return m->getModuleCode() == moduleCode; });

    if (it != assignedModules.end()) {
        assignedModules.erase(it);
        return true;
    }

    return false; // Module not found
}

bool Lecturer::isAvailable(const TimeSlot& timeSlot) const {
    std::string day = timeSlot.getDay();

    // If no schedule for this day, lecturer is available
    if (schedule.find(day) == schedule.end()) {
        return true;
    }

    // Check for time slot overlaps
    for (const auto& occupiedSlot : schedule.at(day)) {
        if (timeSlot.overlaps(*occupiedSlot)) {
            return false; // Conflict found
        }
    }

    return true; // No conflicts
}

bool Lecturer::addToSchedule(TimeSlot* timeSlot) {
    if (!timeSlot) {
        return false;
    }

    std::string day = timeSlot->getDay();

    // Check if this time slot conflicts with existing schedule
    if (!isAvailable(*timeSlot)) {
        return false; // Conflict exists
    }

    // Add time slot to schedule
    if (schedule.find(day) == schedule.end()) {
        schedule[day] = std::vector<TimeSlot*>();
    }

    schedule[day].push_back(timeSlot);
    return true;
}

std::string Lecturer::getDetails() const {
    std::stringstream ss;
    ss << "Lecturer ID: " << lecturerID << ", Name: " << name << ", Department: " << department;
    ss << ", Assigned Modules: " << assignedModules.size();

    return ss.str();
}