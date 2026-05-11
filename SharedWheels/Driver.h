#pragma once
#include "User.h"

// This file defines the Driver class.
// A Driver is a User who owns a vehicle and offers seats to passengers.
// Because Driver inherits from User, it automatically has name and phone already.
// On top of that, a Driver also has extra information about their vehicle.

class Driver : public User
{
    // How many seats are still available in this driver's vehicle
    int seats;

    // How much each seat costs in rupees
    double price;

    // The name of the car or bike, for example "Toyota Corolla"
    string carModel;

    // The number plate of the vehicle, for example "ABC-123"
    string plateNumber;

public:
    // Sets default values so nothing is left as garbage when a Driver is first created
    Driver();

    // Asks the driver to type their details including seats and price
    // This overrides the basic input() from User and adds extra questions
    void input() override;

    // Prints all the driver's details on one line on the screen
    void display() const override;

    // Stores all driver details at once, used when loading from a file
    void set(string n, string p, int s, double pr, string cm = "", string pn = "");

    // Returns the number of available seats
    int getSeats() const;

    // Updates the number of available seats, for example after someone books
    void setSeats(int s);

    // Returns the price per seat
    double getPrice() const;

    // Returns the car model name
    string getCarModel() const;

    // Returns the number plate
    string getPlateNumber() const;

    // These two let us update the car model and plate number if needed
    void setCarModel(string cm);
    void setPlateNumber(string pn);
};
