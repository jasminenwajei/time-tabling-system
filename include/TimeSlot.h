//
// Created by jasmine nwajei on 23/04/2025.
//

#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>

/**
 * @class TimeSlot
 * @brief Represents a time slot in the timetabling system
 *
 * The TimeSlot class defines time periods for scheduling sessions,
 * including day, start time, and end time.
 */
class TimeSlot {
private:
    std::string day;
    std::string startTime;
    std::string endTime;

    // Helper function to convert time string to minutes since midnight
    int timeToMinutes(const std::string& timeStr) const;

public:
    /**
     * @brief Constructor for TimeSlot class
     * @param d Day of the week
     * @param start Start time (format: "HH:MM")
     * @param end End time (format: "HH:MM")
     */
    TimeSlot(const std::string& d, const std::string& start, const std::string& end);

    /**
     * @brief Gets the day
     * @return Day string
     */
    std::string getDay() const;

    /**
     * @brief Gets the start time
     * @return Start time string
     */
    std::string getStartTime() const;

    /**
     * @brief Gets the end time
     * @return End time string
     */
    std::string getEndTime() const;

    /**
     * @brief Gets detailed time slot information
     * @return String containing time slot details
     */
    std::string getTimeSlotDetails() const;

    /**
     * @brief Checks if this time slot overlaps with another
     * @param other Other time slot to check against
     * @return True if there is an overlap, false otherwise
     */
    bool overlaps(const TimeSlot& other) const;
};

#endif // TIMESLOT_H
