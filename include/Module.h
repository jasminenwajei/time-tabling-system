

#ifndef MODULE_H
#define MODULE_H

#include <string>

/**
 * @class Module
 * @brief Represents an academic module in the timetabling system
 *
 * The Module class stores information about academic modules including
 * module code, title, and description.
 */
class Module {
private:
    std::string moduleCode;
    std::string title;
    std::string description;

public:
    /**
     * @brief Constructor for Module class
     * @param code Unique module code
     * @param moduleTitle Module title
     * @param desc Module description (optional)
     */
    Module(const std::string& code, const std::string& moduleTitle, const std::string& desc = "");

    /**
     * @brief Gets the module code
     * @return Module code string
     */
    std::string getModuleCode() const;

    /**
     * @brief Gets the module title
     * @return Module title string
     */
    std::string getTitle() const;

    /**
     * @brief Gets the module description
     * @return Module description string
     */
    std::string getDescription() const;

    /**
     * @brief Gets detailed module information
     * @return String containing module details
     */
    std::string getDetails() const;

    /**
     * @brief Updates the module title
     * @param newTitle New title for the module
     */
    void updateTitle(const std::string& newTitle);

    /**
     * @brief Updates the module description
     * @param newDescription New description for the module
     */
    void updateDescription(const std::string& newDescription);
};

#endif // MODULE_H