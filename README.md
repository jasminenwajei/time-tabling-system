# Timetabling System

A C++ object-oriented timetabling system

The application models the process of creating and managing university timetables by representing students, lecturers, modules, rooms and scheduled teaching sessions while detecting timetable conflicts.

---

## Features

- User management
  - Student accounts
  - Lecturer accounts
  - Administrator accounts

- Academic management
  - Create and manage modules
  - Organise student groups
  - Assign lecturers to modules

- Timetable management
  - Create timetable entries
  - Schedule lectures, seminars and lab sessions
  - Allocate teaching rooms
  - Manage timeslots

- Conflict detection
  - Prevent room clashes
  - Detect lecturer scheduling conflicts
  - Detect student group timetable clashes

- Object-oriented architecture
  - Encapsulation
  - Inheritance
  - Class relationships
  - Separation of responsibilities

---


## Project Structure

```
include/
    Admin.h
    ConflictDetector.h
    GlobalVariables.h
    Lecturer.h
    Module.h
    Room.h
    SessionType.h
    Student.h
    StudentGroup.h
    TimetableEntry.h
    TimetableManager.h
    TimeSlot.h
    User.h
    UserManager.h

src/
    *.cpp implementation files
```

---

## Class Overview

| Class | Responsibility |
|--------|----------------|
| User | Base class for all users |
| Student | Represents students |
| Lecturer | Represents lecturers |
| Admin | Administrative functionality |
| Module | Stores module information |
| StudentGroup | Represents teaching groups |
| Room | Teaching room information |
| TimeSlot | Date and time allocation |
| TimetableEntry | Individual scheduled session |
| TimetableManager | Manages timetable creation |
| ConflictDetector | Detects scheduling conflicts |
| UserManager | Manages system users |

---

## Build Instructions

Clone the repository:

```bash
git clone https://github.com/jasminenwajei/time-tabling-system.git
cd time-tabling-system
```

Configure CMake:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

Run:

```bash
./build/NTUTimetablingSystem
```


Nottingham Trent University

GitHub: https://github.com/jasminenwajei
