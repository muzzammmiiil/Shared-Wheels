#include "Driver.h"
#include <iostream>
#include <algorithm>
using namespace std;

// When a Driver object is created, we set everything to zero or empty
// so there is no random junk data sitting in the variables
Driver::Driver() : seats(0), price(0), carModel(""), plateNumber("") {}

// This function asks the driver to fill in all their details.
// First it calls User::input() to get name and phone (already written in User.cpp).
// Then it asks for seats and price with extra checks to make sure they are valid numbers.
void Driver::input()
{
    User::input();

    cout << "Seats: ";
    cin >> seats;

    // Keep asking if the input was not a number or was zero or negative
    while (cin.fail() || seats <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Must be a number >0: ";
        cin >> seats;
    }

    cout << "Price/seat: ";
    cin >> price;

    // Same check for price
    while (cin.fail() || price <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Must be a number >0: ";
        cin >> price;
    }

    cin.ignore(1000, '\n');
}

// Prints a single line showing everything about this driver
void Driver::display() const
{
    cout << "Driver: " << name << " | Phone: " << phone
         << " | Seats: " << seats << " | Price: Rs." << price
         << " | Car: " << carModel << " | Plate: " << plateNumber << "\n";
}

// Stores all the driver's information at once.
// We call the parent set() first to handle name and phone,
// then store the driver-specific details ourselves.
void Driver::set(string n, string p, int s, double pr, string cm, string pn)
{
    User::set(n, p);
    seats       = s;
    price       = pr;
    carModel    = cm;
    plateNumber = pn;
}

// Simple functions that return or update the stored values
int    Driver::getSeats()            const { return seats; }
void   Driver::setSeats(int s)             { seats = s; }
double Driver::getPrice()            const { return price; }
string Driver::getCarModel()         const { return carModel; }
string Driver::getPlateNumber()      const { return plateNumber; }
void   Driver::setCarModel(string cm)      { carModel = cm; }
void   Driver::setPlateNumber(string pn)   { plateNumber = pn; }
