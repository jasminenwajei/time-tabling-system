cmake_minimum_required(VERSION 3.30)
project(NTUTimetablingSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(NTUTimetablingSystem
        include/User.h
        src/User.cpp
        src/Admin.cpp
        include/Admin.h
        src/Student.cpp
        include/Student.h
        src/Module.cpp
        include/Module.h
        src/StudentGroup.cpp
        include/StudentGroup.h
        src/Lecturer.cpp
        include/Lecturer.h
        src/Room.cpp
        include/Room.h
        src/SessionType.cpp
        include/SessionType.h
        include/TimeSlot.h
        src/TimeSlot.cpp
        include/TimetableEntry.h
        src/TimetableEntry.cpp
        include/TimetableManager.h
        src/TimetableManager.cpp
        include/ConflictDetector.h
        src/ConflictDetector.cpp
        include/UserManager.h
        src/UserManager.cpp
        src/main.cpp
        include/GlobalVariables.h
        src/GlobalVariables.cpp)
