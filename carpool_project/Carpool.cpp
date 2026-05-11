#include "Carpool.h"
#include <iostream>
using namespace std;

// Prints the route and all driver details for this carpool
void Carpool::display() const
{
    cout << "Route: " << src << " -> " << dst << " | Time: " << departureTime << "\n";
    driver.display();
}

// Same as display but also shows the car model separately.
// This is used when a passenger is choosing which ride to book.
void Carpool::displayWithCar() const
{
    cout << "Route: " << src << " -> " << dst << " | Time: " << departureTime << "\n";
    cout << "Driver: " << driver.getName() << " | Phone: " << driver.getPhone()
         << " | Seats: " << driver.getSeats() << " | Price: Rs." << driver.getPrice()
         << " | Car Model: " << driver.getCarModel() << "\n";
}

// Saves all the carpool details into this object.
// This is called both when a driver adds a new ride and when loading from a file.
void Carpool::set(string s, string d, string t, string n, string ph,
                  int se, double pr, string du, string cm, string pn)
{
    src            = s;
    dst            = d;
    departureTime  = t;
    driverUsername = du;
    driver.set(n, ph, se, pr, cm, pn);
}

// Simple functions that return each stored value
string        Carpool::getSrc()            const { return src; }
string        Carpool::getDst()            const { return dst; }
string        Carpool::getDepartureTime()  const { return departureTime; }
string        Carpool::getDriverUsername() const { return driverUsername; }

// Returns the Driver object so the rest of the code can read or change seat count etc.
Driver       &Carpool::getDriver()               { return driver; }
const Driver &Carpool::getDriver()         const { return driver; }
