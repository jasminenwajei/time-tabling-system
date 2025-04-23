//
// Created by jasmine nwajei on 23/04/2025.
//
#include "../include/SessionType.h"

SessionType::SessionType(const std::string& id, const std::string& name)
    : typeID(id), typeName(name) {
}

std::string SessionType::getTypeID() const {
    return typeID;
}

std::string SessionType::getTypeName() const {
    return typeName;
}

std::string SessionType::getSessionDetails() const {
    return "Session Type ID: " + typeID + ", Name: " + typeName;
}

void SessionType::updateTypeName(const std::string& newName) {
    typeName = newName;
}