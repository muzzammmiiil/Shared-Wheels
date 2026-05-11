#pragma once
#include "Carpool.h"
#include "Passenger.h"
#include "Auth.h"

// This file defines CarpoolSystem, which is the brain of the whole program.
// Every major action happens here: adding rides, searching, booking, deleting.
// CarpoolSystem is a Singleton, just like Auth.
// Only one CarpoolSystem object exists, and it manages everything centrally.

class CarpoolSystem
{
    // The list of all carpool rides currently in the system
    Carpool pool[MAX];

    // How many rides are currently stored
    int cnt;

    // Writes all carpool rides to carpool.txt so they are saved permanently
    void saveFile();

    // Reads all carpool rides from carpool.txt when the program starts
    void loadFile();

    // A small helper that reads a menu choice and checks it is within the valid range.
    // Returns false if the user typed something invalid.
    bool getChoice(int &choice, int minVal, int maxVal);

    // Asks the user to type a username and password.
    // If confirm is true, it also asks them to type the password a second time
    // to make sure they did not make a typo.
    void getCreds(string &username, string &password, bool confirm = false);

    // Checks if a time string like "08:30" is a valid time format
    bool isValidTime(const string &t);

    // Lets a logged-in driver add a new carpool ride
    void addCarpool(const string &driverUser);

    // Shows all carpools in the system to anyone
    void viewAll();

    // Shows only the carpools belonging to a specific driver
    void viewMine(const string &username);

    // Lets a logged-in driver delete one of their own carpools
    void deleteCarpool(const string &username);

    // Lets anyone search for rides by typing a source and destination
    void search();

    // Lets a logged-in passenger book a seat on an available ride
    void bookSeat(Passenger &passenger);

    // A browsing feature that lets the passenger flip through rides one by one
    // and book directly from the browse screen
    void slider(Passenger &passenger);

    // Shows the driver menu: register, login, add ride, view rides, delete ride
    void driverPortal();

    // Shows the passenger menu: register, login, browse rides, book a seat
    void passPortal();

    // Private constructor so nobody can create this object directly
    CarpoolSystem();

    // Deleted so the object cannot be copied
    CarpoolSystem(const CarpoolSystem &) = delete;
    CarpoolSystem &operator=(const CarpoolSystem &) = delete;

public:
    // The only way to access the single CarpoolSystem object
    static CarpoolSystem &getInstance();

    // Shows the main menu where the user picks whether they are a driver or passenger
    void menu();
};
