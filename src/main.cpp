//
// Created by jasmine nwajei on 23/04/2025.
//
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>

#include "../include/UserManager.h"
#include "../include/TimetableManager.h"
#include "../include/Module.h"
#include "../include/Room.h"
#include "../include/SessionType.h"
#include "../include/Lecturer.h"
#include "../include/StudentGroup.h"
#include "../include/TimeSlot.h"
#include "../include/GlobalVariables.h"

// Function prototypes
void initializeSystem(UserManager& userManager);
void displayMainMenu();
void displayAdminMenu();
void displayStudentMenu();
void handleAdminOperations(Admin* admin, TimetableManager& timetableManager);
void handleStudentOperations(Student* student, TimetableManager& timetableManager);

// Admin menu handlers
void handleModuleManagement(Admin* admin);
void handleStudentGroupManagement(Admin* admin);
void handleSessionTypeManagement(Admin* admin);
void handleStudentManagement(Admin* admin, UserManager& userManager);
void handleLecturerManagement(Admin* admin);
void handleRoomManagement(Admin* admin);
void handleTimetableManagement(Admin* admin, TimetableManager& timetableManager);
void handleConflictDetection(Admin* admin, TimetableManager& timetableManager);

// Student menu handlers
void handleViewTimetable(Student* student, TimetableManager& timetableManager);
void handleSearchTimetable(Student* student, TimetableManager& timetableManager);
void handleExportTimetable(Student* student, TimetableManager& timetableManager);

// Helper functions
void clearScreen();
void waitForEnter();
std::string getInputString(const std::string& prompt);
int getInputInt(const std::string& prompt, int min = 0, int max = std::numeric_limits<int>::max());

int main() {
    // Create managers
    UserManager userManager;
    TimetableManager timetableManager("2024-2025", "Spring");

    // Initialize system with some test data
    initializeSystem(userManager);

    // Main application loop
    bool running = true;
    while (running) {
        clearScreen();
        std::cout << "=========================================" << std::endl;
        std::cout << "= NTU TIMETABLING SYSTEM               =" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "Academic Year: " << timetableManager.getAcademicYear() << std::endl;
        std::cout << "Semester: " << timetableManager.getSemester() << std::endl;
        std::cout << std::endl;

        displayMainMenu();

        int choice = getInputInt("Enter your choice: ", 1, 3);

        switch (choice) {
            case 1: { // Login
                std::string userId = getInputString("Enter User ID: ");
                std::string password = getInputString("Enter Password: ");

                User* user = userManager.authenticate(userId, password);

                if (user) {
                    std::cout << "Login successful. Welcome, " << user->getName() << "!" << std::endl;

                    // Handle user operations based on type
                    Admin* admin = dynamic_cast<Admin*>(user);
                    if (admin) {
                        handleAdminOperations(admin, timetableManager);
                    } else {
                        Student* student = dynamic_cast<Student*>(user);
                        if (student) {
                            handleStudentOperations(student, timetableManager);
                        }
                    }
                } else {
                    std::cout << "Login failed. Invalid user ID or password." << std::endl;
                    waitForEnter();
                }
                break;
            }
            case 2: {
                std::cout << "About NTU Timetabling System:" << std::endl;
                std::cout << "This system facilitates the management and viewing of academic schedules." << std::endl;
                std::cout << "Developed as part of SOFT20091 Software Design and Implementation module." << std::endl;
                waitForEnter();
                break;
            }
            case 3:
                std::cout << "Exiting the system. Goodbye!" << std::endl;
                running = false;
                break;
        }
    }

    // Clean up global collections
    for (auto module : g_modules) delete module;
    for (auto room : g_rooms) delete room;
    for (auto sessionType : g_sessionTypes) delete sessionType;
    for (auto lecturer : g_lecturers) delete lecturer;
    for (auto group : g_studentGroups) delete group;

    return 0;
}

void initializeSystem(UserManager& userManager) {
    // Create admin user
    Admin* admin = userManager.registerAdmin("admin", "John Smith", "admin123", "Timetabling");

    // Create student user
    Student* student = userManager.registerStudent("student", "Alice Brown", "student123", "N12345678", "Computer Science");

    // Create some sample data
    if (admin) {
        // Create modules
        admin->createModule("SOFT20091", "Software Design and Implementation", "Core module for Year 2 CS students");
        admin->createModule("MATH2010", "Advanced Mathematics", "Mathematics module covering calculus and linear algebra");
        admin->createModule("COMP2005", "Database Systems", "Introduction to database design and SQL");

        // Create student groups
        admin->createStudentGroup("CS-Y2-A", "Computer Science Year 2 Group A");
        admin->createStudentGroup("CS-Y2-B", "Computer Science Year 2 Group B");
        admin->createStudentGroup("MATH-Y2", "Mathematics Year 2");

        // Assign student to group
        admin->assignStudentToGroup("student", "CS-Y2-A");

        // Create session types
        admin->defineSessionType("LEC", "Lecture");
        admin->defineSessionType("LAB", "Laboratory");
        admin->defineSessionType("SEM", "Seminar");

        // Create lecturers
        admin->registerLecturer("lec1", "Dr. Smith", "Computer Science");
        admin->registerLecturer("lec2", "Prof. Jones", "Mathematics");
        admin->registerLecturer("lec3", "Dr. Wilson", "Computer Science");

        // Assign lecturers to modules
        admin->assignLecturerToModule("lec1", "SOFT20091");
        admin->assignLecturerToModule("lec2", "MATH2010");
        admin->assignLecturerToModule("lec3", "COMP2005");

        // Create rooms
        admin->addRoom("MAE202", "Mary Anne Evans Building", 30);
        admin->addRoom("JC006", "John Clare Lecture Theatre", 120);
        admin->addRoom("TL012", "Teaching Lab", 60);
    }
}

void displayMainMenu() {
    std::cout << "Main Menu:" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. About" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void displayAdminMenu() {
    std::cout << "Administrator Menu:" << std::endl;
    std::cout << "1. Module Management" << std::endl;
    std::cout << "2. Student Group Management" << std::endl;
    std::cout << "3. Session Type Management" << std::endl;
    std::cout << "4. Student Management" << std::endl;
    std::cout << "5. Lecturer Management" << std::endl;
    std::cout << "6. Room Management" << std::endl;
    std::cout << "7. Timetable Management" << std::endl;
    std::cout << "8. Conflict Detection" << std::endl;
    std::cout << "9. Logout" << std::endl;
}

void displayStudentMenu() {
    std::cout << "Student Menu:" << std::endl;
    std::cout << "1. View Timetable" << std::endl;
    std::cout << "2. Search Timetable" << std::endl;
    std::cout << "3. Export Timetable" << std::endl;
    std::cout << "4. Logout" << std::endl;
}

void handleAdminOperations(Admin* admin, TimetableManager& timetableManager) {
    bool adminLoggedIn = true;

    while (adminLoggedIn) {
        clearScreen();
        std::cout << "=========================================" << std::endl;
        std::cout << "= ADMINISTRATOR DASHBOARD              =" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "Logged in as: " << admin->getName() << " (" << admin->getDepartment() << ")" << std::endl;
        std::cout << std::endl;

        displayAdminMenu();

        int choice = getInputInt("Enter your choice: ", 1, 9);

        switch (choice) {
            case 1:
                handleModuleManagement(admin);
                break;
            case 2:
                handleStudentGroupManagement(admin);
                break;
            case 3:
                handleSessionTypeManagement(admin);
                break;
            case 4:
                std::cout << "Student Management not fully implemented in this demo." << std::endl;
                waitForEnter();
                break;
            case 5:
                handleLecturerManagement(admin);
                break;
            case 6:
                handleRoomManagement(admin);
                break;
            case 7:
                handleTimetableManagement(admin, timetableManager);
                break;
            case 8:
                handleConflictDetection(admin, timetableManager);
                break;
            case 9:
                std::cout << "Logging out administrator." << std::endl;
                adminLoggedIn = false;
                waitForEnter();
                break;
        }
    }
}

void handleStudentOperations(Student* student, TimetableManager& timetableManager) {
    bool studentLoggedIn = true;

    while (studentLoggedIn) {
        clearScreen();
        std::cout << "=========================================" << std::endl;
        std::cout << "= STUDENT DASHBOARD                    =" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "Logged in as: " << student->getName() << " (" << student->getStudentNumber() << ")" << std::endl;
        std::cout << "Course: " << student->getCourse() << std::endl;
        std::cout << std::endl;

        displayStudentMenu();

        int choice = getInputInt("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:
                handleViewTimetable(student, timetableManager);
                break;
            case 2:
                handleSearchTimetable(student, timetableManager);
                break;
            case 3:
                handleExportTimetable(student, timetableManager);
                break;
            case 4:
                std::cout << "Logging out student." << std::endl;
                studentLoggedIn = false;
                waitForEnter();
                break;
        }
    }
}

void handleStudentManagement(Admin* admin, UserManager& userManager) {
    clearScreen();
    std::cout << "Student Management" << std::endl;
    std::cout << "-----------------" << std::endl;

    // Display existing students
    std::cout << "Existing Students:" << std::endl;
    std::vector<Student*> students = userManager.getAllStudents();
    if (students.empty()) {
        std::cout << "  No students registered yet." << std::endl;
    } else {
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << students[i]->getUserDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Register New Student" << std::endl;
    std::cout << "2. Assign Student to Group" << std::endl;
    std::cout << "3. Update Student Information" << std::endl;
    std::cout << "4. Delete Student" << std::endl;
    std::cout << "5. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 5);

    switch (choice) {
        case 1: {
            std::string id = getInputString("Enter student ID: ");
            std::string name = getInputString("Enter student name: ");
            std::string password = getInputString("Enter student password: ");
            std::string studentNumber = getInputString("Enter student number: ");
            std::string course = getInputString("Enter student course: ");

            Student* student = userManager.registerStudent(id, name, password, studentNumber, course);
            if (student) {
                std::cout << "Student registered successfully." << std::endl;
            } else {
                std::cout << "Failed to register student. ID may already exist." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (students.empty()) {
                std::cout << "No students to assign to groups." << std::endl;
                waitForEnter();
                break;
            }

            if (g_studentGroups.empty()) {
                std::cout << "No student groups available for assignment." << std::endl;
                waitForEnter();
                break;
            }

            int studentIndex = getInputInt("Enter student number: ", 1, students.size()) - 1;
            Student* student = students[studentIndex];

            std::cout << "Selected student: " << student->getUserDetails() << std::endl;
            std::cout << "Available groups:" << std::endl;
            for (size_t i = 0; i < g_studentGroups.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_studentGroups[i]->getDetails() << std::endl;
            }

            int groupIndex = getInputInt("Enter group number to assign student to: ", 1, g_studentGroups.size()) - 1;
            StudentGroup* group = g_studentGroups[groupIndex];

            bool success = admin->assignStudentToGroup(student->getUserID(), group->getGroupID());
            if (success) {
                std::cout << "Student successfully assigned to group." << std::endl;
            } else {
                std::cout << "Failed to assign student to group." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 3: {
            if (students.empty()) {
                std::cout << "No students to update." << std::endl;
                waitForEnter();
                break;
            }

            int studentIndex = getInputInt("Enter student number to update: ", 1, students.size()) - 1;
            Student* student = students[studentIndex];

            std::cout << "Current student details: " << student->getUserDetails() << std::endl;

            std::string oldPassword = getInputString("Enter current password: ");
            std::string newPassword = getInputString("Enter new password: ");

            bool success = student->changePassword(oldPassword, newPassword);
            if (success) {
                std::cout << "Student password updated successfully." << std::endl;
            } else {
                std::cout << "Failed to update password. Current password may be incorrect." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 4: {
            if (students.empty()) {
                std::cout << "No students to delete." << std::endl;
                waitForEnter();
                break;
            }

            int studentIndex = getInputInt("Enter student number to delete: ", 1, students.size()) - 1;
            Student* student = students[studentIndex];
            std::string studentID = student->getUserID();

            // Check if student is assigned to any groups and remove them
            for (auto& group : g_studentGroups) {
                if (group->hasStudent(studentID)) {
                    group->removeStudent(studentID);
                }
            }

            std::cout << "Student " << studentID << " would be deleted from the system." << std::endl;
            std::cout << "Note: In a full implementation, this would remove the student from the database." << std::endl;
            waitForEnter();
            break;
        }
        case 5:
            // Return to Admin Menu
            break;
    }
}

// Admin menu handler implementations
void handleModuleManagement(Admin* admin) {
    clearScreen();
    std::cout << "Module Management" << std::endl;
    std::cout << "----------------" << std::endl;

    // Display existing modules
    std::cout << "Existing Modules:" << std::endl;
    if (g_modules.empty()) {
        std::cout << "  No modules defined yet." << std::endl;
    } else {
        for (size_t i = 0; i < g_modules.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_modules[i]->getDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Add Module" << std::endl;
    std::cout << "2. Edit Module" << std::endl;
    std::cout << "3. Delete Module" << std::endl;
    std::cout << "4. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 4);

    switch (choice) {
        case 1: {
            std::string code = getInputString("Enter module code: ");
            std::string title = getInputString("Enter module title: ");
            std::string description = getInputString("Enter module description: ");

            Module* module = admin->createModule(code, title, description);
            if (module) {
                std::cout << "Module created successfully." << std::endl;
            } else {
                std::cout << "Failed to create module. Module code may already exist." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (g_modules.empty()) {
                std::cout << "No modules to edit." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter module number to edit: ", 1, g_modules.size()) - 1;
            Module* module = g_modules[index];

            std::cout << "Editing module: " << module->getDetails() << std::endl;
            std::string title = getInputString("Enter new title (leave empty to keep current): ");
            std::string description = getInputString("Enter new description (leave empty to keep current): ");

            if (!title.empty()) {
                module->updateTitle(title);
            }

            if (!description.empty()) {
                module->updateDescription(description);
            }

            std::cout << "Module updated: " << module->getDetails() << std::endl;
            waitForEnter();
            break;
        }
        case 3: {
            if (g_modules.empty()) {
                std::cout << "No modules to delete." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter module number to delete: ", 1, g_modules.size()) - 1;

            std::string code = module->getModuleCode();

            g_modules.erase(g_modules.begin() + index);
            delete module;

            std::cout << "Module " << code << " deleted." << std::endl;
            waitForEnter();
            break;
        }
        case 4:
            // Return to Admin Menu
            break;
    }
}

void handleStudentGroupManagement(Admin* admin) {
    clearScreen();
    std::cout << "Student Group Management" << std::endl;
    std::cout << "-----------------------" << std::endl;

    // Display existing student groups
    std::cout << "Existing Student Groups:" << std::endl;
    if (g_studentGroups.empty()) {
        std::cout << "  No student groups defined yet." << std::endl;
    } else {
        for (size_t i = 0; i < g_studentGroups.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_studentGroups[i]->getDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Add Student Group" << std::endl;
    std::cout << "2. Manage Group Members" << std::endl;
    std::cout << "3. Delete Student Group" << std::endl;
    std::cout << "4. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 4);

    switch (choice) {
        case 1: {
            std::string groupID = getInputString("Enter group ID: ");
            std::string groupName = getInputString("Enter group name: ");

            bool success = admin->createStudentGroup(groupID, groupName);
            if (success) {
                std::cout << "Student group created successfully." << std::endl;
            } else {
                std::cout << "Failed to create student group. Group ID may already exist." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (g_studentGroups.empty()) {
                std::cout << "No student groups to manage." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter group number to manage: ", 1, g_studentGroups.size()) - 1;
            StudentGroup* group = g_studentGroups[index];

            std::cout << "Managing group: " << group->getDetails() << std::endl;
            std::cout << "Students in group:" << std::endl;

            const auto& students = group->getStudents();
            if (students.empty()) {
                std::cout << "  No students in this group." << std::endl;
            } else {
                for (size_t i = 0; i < students.size(); ++i) {
                    std::cout << "  " << (i+1) << ". " << students[i]->getUserDetails() << std::endl;
                }
            }

            std::cout << std::endl;
            std::cout << "Operations:" << std::endl;
            std::cout << "1. Add Student to Group" << std::endl;
            std::cout << "2. Remove Student from Group" << std::endl;
            std::cout << "3. Back to Group Management" << std::endl;

            int subChoice = getInputInt("Enter your choice: ", 1, 3);

            switch (subChoice) {
                case 1: {
                    std::string studentID = getInputString("Enter student ID to add: ");
                    bool success = admin->assignStudentToGroup(studentID, group->getGroupID());
                    if (success) {
                        std::cout << "Student added to group successfully." << std::endl;
                    } else {
                        std::cout << "Failed to add student to group. Student may not exist." << std::endl;
                    }
                    break;
                }
                case 2: {
                    if (students.empty()) {
                        std::cout << "No students to remove." << std::endl;
                        break;
                    }

                    int studentIndex = getInputInt("Enter student number to remove: ", 1, students.size()) - 1;
                    std::string studentID = students[studentIndex]->getUserID();

                    bool success = group->removeStudent(studentID);
                    if (success) {
                        std::cout << "Student removed from group successfully." << std::endl;
                    } else {
                        std::cout << "Failed to remove student from group." << std::endl;
                    }
                    break;
                }
                case 3:
                    // Return to Group Management
                    break;
            }

            waitForEnter();
            break;
        }
        case 3: {
            if (g_studentGroups.empty()) {
                std::cout << "No student groups to delete." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter group number to delete: ", 1, g_studentGroups.size()) - 1;

            StudentGroup* group = g_studentGroups[index];
            std::string groupID = group->getGroupID();

            g_studentGroups.erase(g_studentGroups.begin() + index);
            delete group;

            std::cout << "Student group " << groupID << " deleted." << std::endl;
            waitForEnter();
            break;
        }
        case 4:
            // Return to Admin Menu
            break;
    }
}

void handleSessionTypeManagement(Admin* admin) {
    clearScreen();
    std::cout << "Session Type Management" << std::endl;
    std::cout << "----------------------" << std::endl;

    // Display existing session types
    std::cout << "Existing Session Types:" << std::endl;
    if (g_sessionTypes.empty()) {
        std::cout << "  No session types defined yet." << std::endl;
    } else {
        for (size_t i = 0; i < g_sessionTypes.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_sessionTypes[i]->getSessionDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Add Session Type" << std::endl;
    std::cout << "2. Edit Session Type" << std::endl;
    std::cout << "3. Delete Session Type" << std::endl;
    std::cout << "4. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 4);

    switch (choice) {
        case 1: {
            std::string typeID = getInputString("Enter session type ID: ");
            std::string typeName = getInputString("Enter session type name: ");

            bool success = admin->defineSessionType(typeID, typeName);
            if (success) {
                std::cout << "Session type created successfully." << std::endl;
            } else {
                std::cout << "Failed to create session type. Type ID may already exist." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (g_sessionTypes.empty()) {
                std::cout << "No session types to edit." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter session type number to edit: ", 1, g_sessionTypes.size()) - 1;
            SessionType* sessionType = g_sessionTypes[index];

            std::cout << "Editing session type: " << sessionType->getSessionDetails() << std::endl;
            std::string typeName = getInputString("Enter new name (leave empty to keep current): ");

            if (!typeName.empty()) {
                sessionType->updateTypeName(typeName);
            }

            std::cout << "Session type updated: " << sessionType->getSessionDetails() << std::endl;
            waitForEnter();
            break;
        }
        case 3: {
            if (g_sessionTypes.empty()) {
                std::cout << "No session types to delete." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter session type number to delete: ", 1, g_sessionTypes.size()) - 1;

            SessionType* sessionType = g_sessionTypes[index];
            std::string typeID = sessionType->getTypeID();

            g_sessionTypes.erase(g_sessionTypes.begin() + index);
            delete sessionType;

            std::cout << "Session type " << typeID << " deleted." << std::endl;
            waitForEnter();
            break;
        }
        case 4:
            // Return to Admin Menu
            break;
    }
}

void handleLecturerManagement(Admin* admin) {
    clearScreen();
    std::cout << "Lecturer Management" << std::endl;
    std::cout << "-------------------" << std::endl;

    // Display existing lecturers
    std::cout << "Existing Lecturers:" << std::endl;
    if (g_lecturers.empty()) {
        std::cout << "  No lecturers defined yet." << std::endl;
    } else {
        for (size_t i = 0; i < g_lecturers.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_lecturers[i]->getDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Add Lecturer" << std::endl;
    std::cout << "2. Assign Module to Lecturer" << std::endl;
    std::cout << "3. Delete Lecturer" << std::endl;
    std::cout << "4. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 4);

    switch (choice) {
        case 1: {
            std::string lecturerID = getInputString("Enter lecturer ID: ");
            std::string name = getInputString("Enter lecturer name: ");
            std::string department = getInputString("Enter department: ");

            bool success = admin->registerLecturer(lecturerID, name, department);
            if (success) {
                std::cout << "Lecturer registered successfully." << std::endl;
            } else {
                std::cout << "Failed to register lecturer. Lecturer ID may already exist." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (g_lecturers.empty()) {
                std::cout << "No lecturers available." << std::endl;
                waitForEnter();
                break;
            }

            if (g_modules.empty()) {
                std::cout << "No modules available." << std::endl;
                waitForEnter();
                break;
            }

            int lecturerIndex = getInputInt("Enter lecturer number: ", 1, g_lecturers.size()) - 1;
            Lecturer* lecturer = g_lecturers[lecturerIndex];

            std::cout << "Selected lecturer: " << lecturer->getDetails() << std::endl;
            std::cout << "Assigned modules:" << std::endl;

            const auto& assignedModules = lecturer->getAssignedModules();
            if (assignedModules.empty()) {
                std::cout << "  No modules assigned yet." << std::endl;
            } else {
                for (size_t i = 0; i < assignedModules.size(); ++i) {
                    std::cout << "  " << (i+1) << ". " << assignedModules[i]->getDetails() << std::endl;
                }
            }

            std::cout << std::endl;
            std::cout << "Available modules:" << std::endl;
            for (size_t i = 0; i < g_modules.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_modules[i]->getDetails() << std::endl;
            }

            int moduleIndex = getInputInt("Enter module number to assign: ", 1, g_modules.size()) - 1;
            Module* module = g_modules[moduleIndex];

            bool success = admin->assignLecturerToModule(lecturer->getLecturerID(), module->getModuleCode());
            if (success) {
                std::cout << "Module assigned to lecturer successfully." << std::endl;
            } else {
                std::cout << "Failed to assign module to lecturer. Module may already be assigned." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 3: {
            if (g_lecturers.empty()) {
                std::cout << "No lecturers to delete." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter lecturer number to delete: ", 1, g_lecturers.size()) - 1;

            Lecturer* lecturer = g_lecturers[index];
            std::string lecturerID = lecturer->getLecturerID();

            g_lecturers.erase(g_lecturers.begin() + index);
            delete lecturer;

            std::cout << "Lecturer " << lecturerID << " deleted." << std::endl;
            waitForEnter();
            break;
        }
        case 4:
            // Return to Admin Menu
            break;
    }
}

void handleRoomManagement(Admin* admin) {
    clearScreen();
    std::cout << "Room Management" << std::endl;
    std::cout << "---------------" << std::endl;

    // Display existing rooms
    std::cout << "Existing Rooms:" << std::endl;
    if (g_rooms.empty()) {
        std::cout << "  No rooms defined yet." << std::endl;
    } else {
        for (size_t i = 0; i < g_rooms.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_rooms[i]->getDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Add Room" << std::endl;
    std::cout << "2. Delete Room" << std::endl;
    std::cout << "3. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 3);

    switch (choice) {
        case 1: {
            std::string roomID = getInputString("Enter room ID: ");
            std::string location = getInputString("Enter room location: ");
            int capacity = getInputInt("Enter room capacity: ", 1);

            bool success = admin->addRoom(roomID, location, capacity);
            if (success) {
                std::cout << "Room added successfully." << std::endl;
            } else {
                std::cout << "Failed to add room. Room ID may already exist." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (g_rooms.empty()) {
                std::cout << "No rooms to delete." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter room number to delete: ", 1, g_rooms.size()) - 1;

            Room* room = g_rooms[index];
            std::string roomID = room->getRoomID();

            g_rooms.erase(g_rooms.begin() + index);
            delete room;

            std::cout << "Room " << roomID << " deleted." << std::endl;
            waitForEnter();
            break;
        }
        case 3:
            // Return to Admin Menu
            break;
    }
}

void handleTimetableManagement(Admin* admin, TimetableManager& timetableManager) {
    clearScreen();
    std::cout << "Timetable Management" << std::endl;
    std::cout << "--------------------" << std::endl;

    // Display existing timetable entries
    std::cout << "Existing Timetable Entries:" << std::endl;
    const auto& entries = timetableManager.getAllEntries();
    if (entries.empty()) {
        std::cout << "  No timetable entries defined yet." << std::endl;
    } else {
        for (size_t i = 0; i < entries.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << entries[i]->getEntryDetails() << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Operations:" << std::endl;
    std::cout << "1. Create Timetable Entry" << std::endl;
    std::cout << "2. Delete Timetable Entry" << std::endl;
    std::cout << "3. Back to Admin Menu" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 3);

    switch (choice) {
        case 1: {
            // Check all required components are there
            if (g_modules.empty() || g_lecturers.empty() || g_rooms.empty() ||
                g_studentGroups.empty() || g_sessionTypes.empty()) {
                std::cout << "Cannot create timetable entry. Missing required components:" << std::endl;
                if (g_modules.empty()) std::cout << "  - No modules defined" << std::endl;
                if (g_lecturers.empty()) std::cout << "  - No lecturers defined" << std::endl;
                if (g_rooms.empty()) std::cout << "  - No rooms defined" << std::endl;
                if (g_studentGroups.empty()) std::cout << "  - No student groups defined" << std::endl;
                if (g_sessionTypes.empty()) std::cout << "  - No session types defined" << std::endl;
                waitForEnter();
                break;
            }

            int week = getInputInt("Enter week number (1-53): ", 1, 53);

            // Select module
            std::cout << "Available modules:" << std::endl;
            for (size_t i = 0; i < g_modules.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_modules[i]->getDetails() << std::endl;
            }
            int moduleIndex = getInputInt("Select module: ", 1, g_modules.size()) - 1;

            // Select lecturer
            std::cout << "Available lecturers:" << std::endl;
            for (size_t i = 0; i < g_lecturers.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_lecturers[i]->getDetails() << std::endl;
            }
            int lecturerIndex = getInputInt("Select lecturer: ", 1, g_lecturers.size()) - 1;

            // Select room
            std::cout << "Available rooms:" << std::endl;
            for (size_t i = 0; i < g_rooms.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_rooms[i]->getDetails() << std::endl;
            }
            int roomIndex = getInputInt("Select room: ", 1, g_rooms.size()) - 1;

            // Select student group
            std::cout << "Available student groups:" << std::endl;
            for (size_t i = 0; i < g_studentGroups.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_studentGroups[i]->getDetails() << std::endl;
            }
            int groupIndex = getInputInt("Select student group: ", 1, g_studentGroups.size()) - 1;

            // Select session type
            std::cout << "Available session types:" << std::endl;
            for (size_t i = 0; i < g_sessionTypes.size(); ++i) {
                std::cout << "  " << (i+1) << ". " << g_sessionTypes[i]->getSessionDetails() << std::endl;
            }
            int sessionTypeIndex = getInputInt("Select session type: ", 1, g_sessionTypes.size()) - 1;

            // Enter time slot details
            std::string day = getInputString("Enter day of the week: ");
            std::string startTime = getInputString("Enter start time (HH:MM): ");
            std::string endTime = getInputString("Enter end time (HH:MM): ");

            // Create time slot
            TimeSlot* timeSlot = new TimeSlot(day, startTime, endTime);

            // Create timetable entry
            bool success = admin->createTimetableEntry(
                timetableManager,
                week,
                g_modules[moduleIndex]->getModuleCode(),
                g_lecturers[lecturerIndex]->getLecturerID(),
                g_rooms[roomIndex]->getRoomID(),
                g_studentGroups[groupIndex]->getGroupID(),
                g_sessionTypes[sessionTypeIndex]->getTypeID(),
                day,
                startTime,
                endTime
            );

            if (success) {
                std::cout << "Timetable entry created successfully." << std::endl;
            } else {
                std::cout << "Failed to create timetable entry. Check for conflicts." << std::endl;
                delete timeSlot; // Clean up if creation failed
            }
            waitForEnter();
            break;
        }
        case 2: {
            if (entries.empty()) {
                std::cout << "No timetable entries to delete." << std::endl;
                waitForEnter();
                break;
            }

            int index = getInputInt("Enter timetable entry number to delete: ", 1, entries.size()) - 1;
            std::string entryID = entries[index]->getEntryID();

            bool success = timetableManager.deleteEntry(entryID);
            if (success) {
                std::cout << "Timetable entry " << entryID << " deleted." << std::endl;
            } else {
                std::cout << "Failed to delete timetable entry." << std::endl;
            }
            waitForEnter();
            break;
        }
        case 3:
            // Return to Admin Menu
            break;
    }
}

void handleConflictDetection(Admin* admin, TimetableManager& timetableManager) {
    clearScreen();
    std::cout << "Conflict Detection" << std::endl;
    std::cout << "------------------" << std::endl;

    // Check for conflicts
    timetableManager.checkForConflicts();

    if (timetableManager.hasConflicts()) {
        std::cout << "Conflicts detected:" << std::endl;

        auto conflicts = timetableManager.getConflicts();
        for (size_t i = 0; i < conflicts.size(); ++i) {
            std::cout << "Conflict " << (i+1) << ":" << std::endl;
            std::cout << "  1. " << conflicts[i].first->getEntryDetails() << std::endl;
            std::cout << "  2. " << conflicts[i].second->getEntryDetails() << std::endl;

            std::cout << "  Possible resolution: Reschedule one of the sessions to a different time or room." << std::endl;

            std::cout << std::endl;
        }
    } else {
        std::cout << "No conflicts detected in the timetable." << std::endl;
    }

    waitForEnter();
}

// Student menu handler implementations
void handleViewTimetable(Student* student, TimetableManager& timetableManager) {
    clearScreen();
    std::cout << "View Timetable" << std::endl;
    std::cout << "-------------" << std::endl;

    std::cout << "Select week number:" << std::endl;
    std::cout << "1. Current week" << std::endl;
    std::cout << "2. Specific week" << std::endl;
    std::cout << "3. All weeks" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 3);

    int week;
    switch (choice) {
        case 1:
            week = 1;
            break;
        case 2:
            week = getInputInt("Enter week number (1-53): ", 1, 53);
            break;
        case 3:
            week = -1; // All weeks
            break;
    }

    // View timetable
    std::vector<TimetableEntry*> timetable = student->viewTimetable(timetableManager, week);

    if (timetable.empty()) {
        std::cout << "No timetable entries found for the selected week(s)." << std::endl;
    } else {
        std::cout << "Found " << timetable.size() << " timetable entries:" << std::endl;
        for (size_t i = 0; i < timetable.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << timetable[i]->getEntryDetails() << std::endl;
        }
    }

    waitForEnter();
}

void handleSearchTimetable(Student* student, TimetableManager& timetableManager) {
    clearScreen();
    std::cout << "Search Timetable" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "Search options:" << std::endl;
    std::cout << "1. By week number" << std::endl;
    std::cout << "2. By module" << std::endl;
    std::cout << "3. By room" << std::endl;
    std::cout << "4. By lecturer" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 4);

    int week = -1;
    std::string moduleCode = "";
    std::string roomID = "";
    std::string lecturerID = "";

    // Handle week number search
    if (choice == 1) {
        week = getInputInt("Enter week number (1-53): ", 1, 53);
    }
    // Handle module search
    else if (choice == 2) {
        if (g_modules.empty()) {
            std::cout << "No modules defined in the system." << std::endl;
            waitForEnter();
            return;
        }

        std::cout << "Available modules:" << std::endl;
        for (size_t i = 0; i < g_modules.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_modules[i]->getDetails() << std::endl;
        }

        int moduleIndex = getInputInt("Select module: ", 1, g_modules.size()) - 1;
        moduleCode = g_modules[moduleIndex]->getModuleCode();
    }
    // Handle room search
    else if (choice == 3) {
        if (g_rooms.empty()) {
            std::cout << "No rooms defined in the system." << std::endl;
            waitForEnter();
            return;
        }

        std::cout << "Available rooms:" << std::endl;
        for (size_t i = 0; i < g_rooms.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_rooms[i]->getDetails() << std::endl;
        }

        int roomIndex = getInputInt("Select room: ", 1, g_rooms.size()) - 1;
        roomID = g_rooms[roomIndex]->getRoomID();
    }
    // Handle lecturer search
    else if (choice == 4) {
        if (g_lecturers.empty()) {
            std::cout << "No lecturers defined in the system." << std::endl;
            waitForEnter();
            return;
        }

        std::cout << "Available lecturers:" << std::endl;
        for (size_t i = 0; i < g_lecturers.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << g_lecturers[i]->getDetails() << std::endl;
        }

        int lecturerIndex = getInputInt("Select lecturer: ", 1, g_lecturers.size()) - 1;
        lecturerID = g_lecturers[lecturerIndex]->getLecturerID();
    }

    // Search timetable
    std::vector<TimetableEntry*> results = student->searchTimetable(
        timetableManager, week, moduleCode, roomID, lecturerID);

    if (results.empty()) {
        std::cout << "No matching timetable entries found." << std::endl;
    } else {
        std::cout << "Found " << results.size() << " matching entries:" << std::endl;
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << "  " << (i+1) << ". " << results[i]->getEntryDetails() << std::endl;
        }
    }

    waitForEnter();
}

void handleExportTimetable(Student* student, TimetableManager& timetableManager) {
    clearScreen();
    std::cout << "Export Timetable" << std::endl;
    std::cout << "---------------" << std::endl;

    std::cout << "Select week to export:" << std::endl;
    std::cout << "1. Current week" << std::endl;
    std::cout << "2. Specific week" << std::endl;
    std::cout << "3. All weeks" << std::endl;

    int choice = getInputInt("Enter your choice: ", 1, 3);

    int week;
    switch (choice) {
        case 1:
            week = 1;
            break;
        case 2:
            week = getInputInt("Enter week number (1-53): ", 1, 53);
            break;
        case 3:
            week = -1; // All weeks
            break;
    }

    std::string filename = getInputString("Enter filename for export (e.g., timetable.csv): ");

    // Export timetable
    bool success = student->exportTimetable(timetableManager, filename, week);

    if (success) {
        std::cout << "Timetable exported successfully to " << filename << "." << std::endl;
    } else {
        std::cout << "Failed to export timetable." << std::endl;
    }

    waitForEnter();
}

// Helper functions implementation
void clearScreen() {
    std::cout << std::string(50, '\n');
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getInputString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int getInputInt(const std::string& prompt, int min, int max) {
    int input;
    bool validInput = false;

    do {
        std::cout << prompt;
        if (std::cin >> input) {
            // Clear the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (input >= min && input <= max) {
                validInput = true;
            } else {
                std::cout << "Please enter a number between " << min << " and " << max << "." << std::endl;
            }
        } else {
            // Clear the error flag
            std::cin.clear();

            // Clear the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter a number." << std::endl;
        }
    } while (!validInput);

    return input;
}
