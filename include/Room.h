//
// Created by jasmine nwajei on 23/04/2025.
//

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>
#include "TimeSlot.h"

/**
 * @class Room
 * @brief Represents a room in the timetabling system
 *
 * The Room class manages information about rooms, their capacity,
 * and availability.
 */
class Room {
private:
    std::string roomID;
    std::string location;
    int capacity;
    std::map<std::string, std::vector<TimeSlot*>> schedule; // Day -> List of occupied time slots

public:
    /**
     * @brief Constructor for Room class
     * @param id Unique room identifier
     * @param loc Room location
     * @param cap Room capacity
     */
    Room(const std::string& id, const std::string& loc, int cap);

    /**
     * @brief Gets the room ID
     * @return Room ID string
     */
    std::string getRoomID() const;

    /**
     * @brief Gets the room location
     * @return Location string
     */
    std::string getLocation() const;

    /**
     * @brief Gets the room capacity
     * @return Capacity as integer
     */
    int getCapacity() const;

    /**
     * @brief Gets detailed room information
     * @return String containing room details
     */
    std::string getDetails() const;

    /**
     * @brief Checks if room is available at a specific time
     * @param timeSlot Time slot to check
     * @return True if room is available, false if booked
     */
    bool isAvailable(const TimeSlot& timeSlot) const;

    /**
     * @brief Books a time slot for the room
     * @param timeSlot Time slot to book
     * @return True if booking successful, false if conflict exists
     */
    bool bookTimeSlot(TimeSlot* timeSlot);
};

#endif // ROOM_H
