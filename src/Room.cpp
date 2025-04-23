//
// Created by jasmine nwajei on 23/04/2025.
//

#include "../include/Room.h"
#include <sstream>

Room::Room(const std::string& id, const std::string& loc, int cap)
    : roomID(id), location(loc), capacity(cap) {
}

std::string Room::getRoomID() const {
    return roomID;
}

std::string Room::getLocation() const {
    return location;
}

int Room::getCapacity() const {
    return capacity;
}

std::string Room::getDetails() const {
    std::stringstream ss;
    ss << "Room ID: " << roomID << ", Location: " << location << ", Capacity: " << capacity;
    return ss.str();
}

bool Room::isAvailable(const TimeSlot& timeSlot) const {
    std::string day = timeSlot.getDay();

    // If no schedule for this day, room is available
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

bool Room::bookTimeSlot(TimeSlot* timeSlot) {
    if (!timeSlot) {
        return false;
    }

    std::string day = timeSlot->getDay();

    // Check if this time slot conflicts with existing bookings
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