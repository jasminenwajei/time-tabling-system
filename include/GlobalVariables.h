
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <vector>
#include "Module.h"
#include "Student.h"
#include "Lecturer.h"
#include "Room.h"
#include "SessionType.h"
#include "StudentGroup.h"

// Declare external variables
extern std::vector<Module*> g_modules;
extern std::vector<Student*> g_students;
extern std::vector<Lecturer*> g_lecturers;
extern std::vector<Room*> g_rooms;
extern std::vector<SessionType*> g_sessionTypes;
extern std::vector<StudentGroup*> g_studentGroups;

#endif // GLOBAL_VARIABLES_H