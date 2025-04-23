
#include "../include/TimetableEntry.h"
#include <sstream>

TimetableEntry::TimetableEntry(const std::string& id, int week, Module* mod, Lecturer* lec,
                             Room* rm, StudentGroup* group, SessionType* session, TimeSlot* time)
    : entryID(id), weekNumber(week), module(mod), lecturer(lec),
      room(rm), studentGroup(group), sessionType(session), timeSlot(time) {

    // Register the time slot with the lecturer and room
    if (lecturer && timeSlot) {
        lecturer->addToSchedule(timeSlot);
    }

    if (room && timeSlot) {
        room->bookTimeSlot(timeSlot);
    }
}

TimetableEntry::~TimetableEntry() {
    delete timeSlot;
}

std::string TimetableEntry::getEntryID() const {
    return entryID;
}

int TimetableEntry::getWeekNumber() const {
    return weekNumber;
}

Module* TimetableEntry::getModule() const {
    return module;
}

Lecturer* TimetableEntry::getLecturer() const {
    return lecturer;
}

Room* TimetableEntry::getRoom() const {
    return room;
}

StudentGroup* TimetableEntry::getStudentGroup() const {
    return studentGroup;
}

SessionType* TimetableEntry::getSessionType() const {
    return sessionType;
}

TimeSlot* TimetableEntry::getTimeSlot() const {
    return timeSlot;
}

std::string TimetableEntry::getEntryDetails() const {
    std::stringstream ss;
    ss << "Entry ID: " << entryID
       << ", Week: " << weekNumber
       << ", Module: " << module->getTitle()
       << " (" << module->getModuleCode() << ")"
       << ", Lecturer: " << lecturer->getName()
       << ", Room: " << room->getRoomID()
       << ", Group: " << studentGroup->getGroupName()
       << ", Session: " << sessionType->getTypeName()
       << ", Time: " << timeSlot->getTimeSlotDetails();

    return ss.str();
}

bool TimetableEntry::checkConflict(const TimetableEntry& other) const {
    // Check if entries are for the same week
    if (weekNumber != other.weekNumber) {
        return false;
    }

    // Check if there's a time conflict
    if (!timeSlot->overlaps(*other.timeSlot)) {
        return false;
    }

    // Check if the same room is booked
    if (room->getRoomID() == other.room->getRoomID()) {
        return true;
    }

    // Check if the same lecturer is booked
    if (lecturer->getLecturerID() == other.lecturer->getLecturerID()) {
        return true;
    }

    // Check if the same student group is booked
    if (studentGroup->getGroupID() == other.studentGroup->getGroupID()) {
        return true;
    }

    // No conflict
    return false;
}