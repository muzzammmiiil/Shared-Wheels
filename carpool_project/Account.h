#pragma once
#include <string>
using namespace std;

// This file defines the Account class.
// An Account stores the login information for one person.
// Think of it like a row in a login database: username, password, and contact info.
// For drivers it also stores their name, phone, car model, and plate number
// because that info is tied to their account when they register.

class Account
{
    // The username and password used to log in
    string username;
    string password;

    // The phone number linked to this account
    string phone;

    // These four are only used for driver accounts
    string carModel;
    string plateNumber;
    string driverName;
    string driverPhone;

public:
    // Stores the basic login details. Phone is optional so it has a default value of empty.
    void set(string un, string pw, string ph = "");

    // Stores the extra vehicle and personal info for driver accounts
    void setDriverInfo(string dn, string dp, string cm, string pn);

    // These functions return each piece of stored information one by one
    string getUsername()    const;
    string getPassword()    const;
    string getPhone()       const;
    string getCarModel()    const;
    string getPlateNumber() const;
    string getDriverName()  const;
    string getDriverPhone() const;
};
