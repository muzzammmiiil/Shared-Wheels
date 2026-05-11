#pragma once
#include "Account.h"

// The maximum number of accounts the system can hold
const int MAX = 100;

// This file defines the Auth class which handles all login and registration.
// Auth is a Singleton, meaning only ONE Auth object can ever exist in the program.
// This makes sense because there should only be one central place that checks passwords.
// Think of it like a security guard at the door: you only need one guard, not a hundred.

class Auth
{
    // Two separate lists: one for driver accounts, one for passenger accounts
    Account driverAccounts[MAX];
    Account passengerAccounts[MAX];

    // Counters to track how many accounts are in each list
    int driverCount;
    int passengerCount;

    // Reads passenger accounts from a text file into memory when the program starts
    void load(const string &filename, Account accounts[], int &count);

    // Reads driver accounts from driver_acc.txt into memory when the program starts
    void loadDrivers();

    // Writes all driver accounts back to driver_acc.txt to save any changes
    void saveDrivers();

    // Writes all passenger accounts back to the given file to save any changes
    void save(const string &filename, Account accounts[], int count);

    // Checks if a username already exists in a list so we do not allow duplicates
    bool exists(Account accounts[], int count, const string &username);

    // Checks if the given username and password match any account in the list
    bool check(Account accounts[], int count, const string &username, const string &password);

    // The constructor is private so nobody can create an Auth object directly.
    // The only way to get the Auth object is through getInstance() below.
    Auth();

    // These are deleted so nobody can copy the Auth object either
    Auth(const Auth &) = delete;
    Auth &operator=(const Auth &) = delete;

public:
    // This is how you get the one and only Auth object.
    // Every part of the code that needs Auth calls Auth::getInstance()
    static Auth &getInstance();

    // Registers a new driver account. Returns false if the username is already taken.
    bool regDriver(const string &username, const string &password,
                   const string &driverName, const string &driverPhone,
                   const string &carModel,   const string &plateNumber);

    // Registers a new passenger account. Returns false if the username is already taken.
    bool regPass(const string &username, const string &password, const string &phone);

    // Returns true if the driver username and password are correct
    bool loginDriver(const string &username, const string &password);

    // Returns true if the passenger username and password are correct
    bool loginPass(const string &username, const string &password);

    // Finds and returns the phone number saved for a passenger account
    string getPassPhone(const string &username);

    // Finds and returns a pointer to a driver's full Account object.
    // Used when we need to read car model, plate number, etc. after login.
    Account *getDriverAccount(const string &username);
};
