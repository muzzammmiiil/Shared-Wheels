 SHARED WHEELS (CARPOOL MANAGEMENT SYSTEM) — README

GROUP MEMBERS:

Syed Muhammad Talha Abdullah

Muhammad Muzzammil

Syed Shahmeer Javaid

HOW TO COMPILE:

Make sure you have g++ installed (MinGW on Windows, or GCC on Linux/Mac).

Open a terminal/command prompt inside this project folder and run:

  g++ -std=c++11 -o carpool main.cpp Utils.cpp User.cpp Driver.cpp Passenger.cpp Account.cpp Auth.cpp Carpool.cpp CarpoolSystem.cpp

This will produce an executable called "carpool" (or "carpool.exe" on Windows).

HOW TO RUN:

  Windows : carpool.exe
  Linux   : ./carpool

Three .txt files will be created automatically in the same folder
to persist data between runs:
  - carpool.txt      (all carpool rides)
  - driver_acc.txt   (driver accounts)
  - pass_acc.txt     (passenger accounts)


PROBLEM DOMAIN:

A console-based Carpool Management System that allows:
  - Drivers  : Register/login, add carpool rides, view their rides, delete rides.
  - Passengers: Register/login, browse available rides (slider view), book a seat.

Data is saved to text files so it persists across sessions.


FILE STRUCTURE:

  Utils.h / Utils.cpp           — toLower() utility function
  User.h / User.cpp             — Abstract base class User
  Driver.h / Driver.cpp         — Driver class (inherits User)
  Passenger.h / Passenger.cpp   — Passenger class (inherits User)
  Account.h / Account.cpp       — Account data holder for authentication
  Auth.h / Auth.cpp             — Auth Singleton: register & login
  Carpool.h / Carpool.cpp       — Carpool ride data class
  CarpoolSystem.h / CarpoolSystem.cpp — Core system Singleton (all logic)
  CarpoolFacade.h               — Facade class (simplifies entry point)
  Repository.h                  — Generic template Repository class + helpers
  main.cpp                      — Entry point + CarpoolFacade implementation


OOP FEATURES IMPLEMENTED:

1. CLASSES & OBJECTS
   - User, Driver, Passenger, Account, Auth, Carpool, CarpoolSystem, CarpoolFacade

2. INHERITANCE
   - Driver   inherits from User
   - Passenger inherits from User

3. POLYMORPHISM
   - Virtual display() in User, overridden in Driver and Passenger
   - Virtual input()   in User, overridden in Driver and Passenger

4. ABSTRACTION
   - User is an abstract class (pure virtual display())

5. ENCAPSULATION
   - All class data is private/protected with getters and setters

6. SINGLETON DESIGN PATTERN
   - Auth::getInstance()          — single Auth object
   - CarpoolSystem::getInstance() — single CarpoolSystem object

7. FACADE DESIGN PATTERN
   - CarpoolFacade hides system complexity behind a single start() call

8. TEMPLATE CLASS
   - Repository<T> — generic add/remove/find/sort/filter container

9. TEMPLATE FUNCTIONS
   - findByName<T>(), displayAll<T>(), sortedCopy<T,Cmp>()

10. FILE I/O
    - All data persisted to .txt files using fstream (ofstream / ifstream)

11. STL USAGE
    - vector, map, algorithm (find_if, sort, transform, all_of) 

12. INPUT VALIDATION
    - Phone number length & digit checks
    - Time format validation (HH:MM)
    - cin.fail() checks with recovery throughout

