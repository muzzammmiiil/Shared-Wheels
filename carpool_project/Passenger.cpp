#include "Passenger.h"
#include <iostream>
using namespace std;

// When a Passenger is created, the booked route starts as empty
// because they have not booked anything yet
Passenger::Passenger() : bookedSrc(""), bookedDst("") {}

// Only asks for a name since phone is already stored in their account
void Passenger::input()
{
    cout << "Your Name: ";
    getline(cin, name);

    while (name.empty())
    {
        cout << "Not empty: ";
        getline(cin, name);
    }

    // Phone is left empty here, it gets filled from the account later
    phone = "";
}

// Shows the passenger's details on screen.
// If they have already booked a ride, it also shows the route.
void Passenger::display() const
{
    cout << "Passenger: " << name << " | Phone: " << phone;

    if (!bookedSrc.empty())
        cout << " | Booked: " << bookedSrc << " -> " << bookedDst;

    cout << "\n";
}

// Saves the route the passenger just booked
void Passenger::setBooking(string src, string dst)
{
    bookedSrc = src;
    bookedDst = dst;
}

// Returns the saved source and destination
string Passenger::getBookedSrc() const { return bookedSrc; }
string Passenger::getBookedDst() const { return bookedDst; }
