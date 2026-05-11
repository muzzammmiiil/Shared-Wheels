#include "Auth.h"
#include "Utils.h"
#include <fstream>
#include <sstream>
using namespace std;

// Reads passenger accounts from a file.
// Each line in the file looks like: username|password|phone
// We split each line by the | character and store the pieces into an Account.
void Auth::load(const string &filename, Account accounts[], int &count)
{
    ifstream file(filename.c_str());
    count = 0;
    string line;
    while (getline(file, line) && count < MAX)
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string u, p, ph;
        getline(ss, u,  '|');
        getline(ss, p,  '|');
        getline(ss, ph);
        if (!u.empty())
            accounts[count++].set(u, p, ph);
    }
}

// Reads driver accounts from driver_acc.txt.
// Driver lines have more fields: username|password|phone|driverName|driverPhone|carModel|plate
void Auth::loadDrivers()
{
    ifstream file("driver_acc.txt");
    driverCount = 0;
    string line;
    while (getline(file, line) && driverCount < MAX)
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string u, p, ph, dn, dp, cm, pn;
        getline(ss, u,  '|');
        getline(ss, p,  '|');
        getline(ss, ph, '|');
        getline(ss, dn, '|');
        getline(ss, dp, '|');
        getline(ss, cm, '|');
        getline(ss, pn);
        if (!u.empty())
        {
            driverAccounts[driverCount].set(u, p, ph);
            driverAccounts[driverCount].setDriverInfo(dn, dp, cm, pn);
            driverCount++;
        }
    }
}

// Writes all driver accounts back to the file so data is not lost when the program closes
void Auth::saveDrivers()
{
    ofstream file("driver_acc.txt");
    for (int i = 0; i < driverCount; i++)
        file << driverAccounts[i].getUsername()    << "|"
             << driverAccounts[i].getPassword()    << "|"
             << driverAccounts[i].getPhone()       << "|"
             << driverAccounts[i].getDriverName()  << "|"
             << driverAccounts[i].getDriverPhone() << "|"
             << driverAccounts[i].getCarModel()    << "|"
             << driverAccounts[i].getPlateNumber() << "\n";
}

// Writes all passenger accounts back to the given file
void Auth::save(const string &filename, Account accounts[], int count)
{
    ofstream file(filename.c_str());
    for (int i = 0; i < count; i++)
        file << accounts[i].getUsername() << "|"
             << accounts[i].getPassword() << "|"
             << accounts[i].getPhone()    << "\n";
}

// Loops through the list and checks if any account has this username.
// We convert both to lowercase so "Ali" and "ali" are treated as the same.
bool Auth::exists(Account accounts[], int count, const string &username)
{
    for (int i = 0; i < count; i++)
        if (toLower(accounts[i].getUsername()) == toLower(username))
            return true;
    return false;
}

// Loops through and checks if any account matches both the username AND password
bool Auth::check(Account accounts[], int count, const string &username, const string &password)
{
    for (int i = 0; i < count; i++)
        if (toLower(accounts[i].getUsername()) == toLower(username) &&
            accounts[i].getPassword() == password)
            return true;
    return false;
}

// When Auth is first created it immediately loads all saved accounts from files.
// This happens automatically when getInstance() is called for the first time.
Auth::Auth() : driverCount(0), passengerCount(0)
{
    loadDrivers();
    load("pass_acc.txt", passengerAccounts, passengerCount);
}

// This is the only way to get the Auth object.
// The "static" keyword means the object is created once and reused every time.
Auth &Auth::getInstance()
{
    static Auth instance;
    return instance;
}

// Adds a new driver account if the username is not already taken
bool Auth::regDriver(const string &username, const string &password,
                     const string &driverName, const string &driverPhone,
                     const string &carModel,   const string &plateNumber)
{
    if (exists(driverAccounts, driverCount, username) || driverCount >= MAX)
        return false;
    driverAccounts[driverCount].set(username, password);
    driverAccounts[driverCount].setDriverInfo(driverName, driverPhone, carModel, plateNumber);
    driverCount++;
    saveDrivers();
    return true;
}

// Adds a new passenger account if the username is not already taken
bool Auth::regPass(const string &username, const string &password, const string &phone)
{
    if (exists(passengerAccounts, passengerCount, username) || passengerCount >= MAX)
        return false;
    passengerAccounts[passengerCount++].set(username, password, phone);
    save("pass_acc.txt", passengerAccounts, passengerCount);
    return true;
}

// Checks if the driver login details are correct
bool Auth::loginDriver(const string &username, const string &password)
{
    return check(driverAccounts, driverCount, username, password);
}

// Checks if the passenger login details are correct
bool Auth::loginPass(const string &username, const string &password)
{
    return check(passengerAccounts, passengerCount, username, password);
}

// Finds the phone number stored for a passenger by their username
string Auth::getPassPhone(const string &username)
{
    for (int i = 0; i < passengerCount; i++)
        if (toLower(passengerAccounts[i].getUsername()) == toLower(username))
            return passengerAccounts[i].getPhone();
    return "";
}

// Finds and returns the full Account object for a driver.
// Returns nullptr (nothing) if no driver with that username exists.
Account *Auth::getDriverAccount(const string &username)
{
    for (int i = 0; i < driverCount; i++)
        if (toLower(driverAccounts[i].getUsername()) == toLower(username))
            return &driverAccounts[i];
    return nullptr;
}
