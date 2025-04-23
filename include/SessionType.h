//
// Created by jasmine nwajei on 23/04/2025.
//

#ifndef SESSION_TYPE_H
#define SESSION_TYPE_H

#include <string>

/**
 * @class SessionType
 * @brief Represents a type of academic session in the timetabling system
 *
 * The SessionType class defines different types of academic sessions
 * such as lectures, labs, or seminars.
 */
class SessionType {
private:
    std::string typeID;
    std::string typeName;

public:
    /**
     * @brief Constructor for SessionType class
     * @param id Unique type identifier
     * @param name Type name (e.g., "Lecture", "Lab", "Seminar")
     */
    SessionType(const std::string& id, const std::string& name);

    /**
     * @brief Gets the type ID
     * @return Type ID string
     */
    std::string getTypeID() const;

    /**
     * @brief Gets the type name
     * @return Type name string
     */
    std::string getTypeName() const;

    /**
     * @brief Gets detailed session type information
     * @return String containing session type details
     */
    std::string getSessionDetails() const;

    /**
     * @brief Updates the type name
     * @param newName New name for the session type
     */
    void updateTypeName(const std::string& newName);
};

#endif // SESSION_TYPE_H