#pragma once
#include "User.h"

// This file defines the Passenger class.
// A Passenger is a User who wants to find and book a carpool ride.
// Just like Driver, Passenger inherits name and phone from User.
// The only extra thing a Passenger has is a record of which ride they booked.

class Passenger : public User
{
    // These store where the passenger is travelling from and to
    // after they book a ride. They start empty until a booking is made.
    string bookedSrc;
    string bookedDst;

public:
    // Sets the booking info to empty when a Passenger is first created
    Passenger();

    // Asks the passenger to type only their name.
    // Passengers do not need to enter a phone here because
    // their phone is already saved when they registered their account.
    void input() override;

    // Prints the passenger's name, phone, and their booked route if they have one
    void display() const override;

    // Saves the source and destination after a passenger books a ride
    void setBooking(string src, string dst);

    // Returns where the passenger is travelling from
    string getBookedSrc() const;

    // Returns where the passenger is travelling to
    string getBookedDst() const;
};
