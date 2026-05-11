#pragma once
#include <string>
using namespace std;

// This file defines the User class.
// A User is the most basic type of person in our system.
// Both a Driver and a Passenger are types of Users, so they share this base.
// Think of User like a blank form that says "every person has a name and phone number".

// The word "abstract" means we can never create a plain User object directly.
// You can only create a Driver or a Passenger, not a nameless generic User.
// This is forced by the pure virtual display() function at the bottom.

class User
{
protected:
    // These two pieces of information belong to every person in the system.
    // "protected" means Driver and Passenger can also see and use these variables.
    string name;
    string phone;

public:
    // input() asks the user to type their name and phone number.
    // The "virtual" keyword means Driver and Passenger can replace this with their own version.
    virtual void input();

    // set() lets us directly assign a name and phone number from code instead of typing.
    void set(string n, string p);

    // These two functions simply return the name and phone number stored inside.
    string getName()  const;
    string getPhone() const;

    // display() prints the person's details on screen.
    // It has no body here because every type of person displays differently.
    // Driver and Passenger each write their own version of display().
    // The "= 0" means this MUST be written in the child class, it cannot be skipped.
    virtual void display() const = 0;

    // This destructor makes sure memory is cleaned up properly
    // when a Driver or Passenger object is deleted.
    virtual ~User() {}
};
