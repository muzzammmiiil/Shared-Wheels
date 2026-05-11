#include "Account.h"

// Saves the username, password, and phone into this account
void Account::set(string un, string pw, string ph)
{
    username = un;
    password = pw;
    phone    = ph;
}

// Saves the driver-specific details into this account.
// This is called only when registering a driver, not a passenger.
void Account::setDriverInfo(string dn, string dp, string cm, string pn)
{
    driverName  = dn;
    driverPhone = dp;
    carModel    = cm;
    plateNumber = pn;
}

// Each of these simply hands back one stored value when someone asks for it
string Account::getUsername()    const { return username; }
string Account::getPassword()    const { return password; }
string Account::getPhone()       const { return phone; }
string Account::getCarModel()    const { return carModel; }
string Account::getPlateNumber() const { return plateNumber; }
string Account::getDriverName()  const { return driverName; }
string Account::getDriverPhone() const { return driverPhone; }
