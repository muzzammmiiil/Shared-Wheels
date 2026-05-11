#pragma once
#include "Driver.h"

// This file defines the Carpool class.
// A Carpool represents one ride being offered by a driver.
// It stores where the ride starts, where it ends, what time it leaves,
// and all the driver's details for that ride.

class Carpool
{
    // The city or place the ride starts from
    string src;

    // The city or place the ride is going to
    string dst;

    // The time the ride leaves, stored as text like "08:30"
    string departureTime;

    // The username of the driver who created this carpool.
    // We store this so we know which driver owns which ride.
    string driverUsername;

    // All the driver's details for this specific ride
    Driver driver;

public:
    // Prints the basic route and driver info on screen
    void display() const;

    // Prints the route and also includes the car model, used when booking
    void displayWithCar() const;

    // Stores all the information for this carpool at once
    void set(string s, string d, string t, string n, string ph, int se, double pr,
             string du = "", string cm = "", string pn = "");

    // Returns each piece of stored information
    string getSrc()           const;
    string getDst()           const;
    string getDepartureTime() const;
    string getDriverUsername()const;

    // Returns the Driver object so we can read or update seats, price, etc.
    Driver       &getDriver();
    const Driver &getDriver() const;
};
