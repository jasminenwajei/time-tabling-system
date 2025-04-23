//
// Created by jasmine nwajei on 23/04/2025.
//

#include "../include/TimeSlot.h"
#include <sstream>

TimeSlot::TimeSlot(const std::string& d, const std::string& start, const std::string& end)
    : day(d), startTime(start), endTime(end) {
}

std::string TimeSlot::getDay() const {
    return day;
}

std::string TimeSlot::getStartTime() const {
    return startTime;
}

std::string TimeSlot::getEndTime() const {
    return endTime;
}

std::string TimeSlot::getTimeSlotDetails() const {
    std::stringstream ss;
    ss << day << " " << startTime << " - " << endTime;
    return ss.str();
}

int TimeSlot::timeToMinutes(const std::string& timeStr) const {
    // Assuming format is "HH:MM"
    int hours = std::stoi(timeStr.substr(0, 2));
    int minutes = std::stoi(timeStr.substr(3, 2));
    return hours * 60 + minutes;
}

bool TimeSlot::overlaps(const TimeSlot& other) const {
    // Different days cannot overlap
    if (day != other.day) {
        return false;
    }

    // Convert times to minutes for easier comparison
    int thisStart = timeToMinutes(startTime);
    int thisEnd = timeToMinutes(endTime);
    int otherStart = timeToMinutes(other.startTime);
    int otherEnd = timeToMinutes(other.endTime);

    // Check for overlap
    return (thisStart < otherEnd && thisEnd > otherStart);
}