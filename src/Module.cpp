

#include "../include/Module.h"

Module::Module(const std::string& code, const std::string& moduleTitle, const std::string& desc)
    : moduleCode(code), title(moduleTitle), description(desc) {
}

std::string Module::getModuleCode() const {
    return moduleCode;
}

std::string Module::getTitle() const {
    return title;
}

std::string Module::getDescription() const {
    return description;
}

std::string Module::getDetails() const {
    return "Module Code: " + moduleCode + ", Title: " + title +
           (description.empty() ? "" : ", Description: " + description);
}

void Module::updateTitle(const std::string& newTitle) {
    title = newTitle;
}

void Module::updateDescription(const std::string& newDescription) {
    description = newDescription;
}