#include "User.h"
#include <iostream>
#include <algorithm>
using namespace std;

// This is the actual code for all the User functions declared in User.h.

// This function asks the person to type their name and phone number.
// It keeps asking again if they leave the name blank.
// It also keeps asking for the phone until it is exactly 11 digits and all numbers.
void User::input()
{
    cout << "Name: ";
    getline(cin, name);

    // Keep asking if the name box was left empty
    while (name.empty())
    {
        cout << "Not empty: ";
        getline(cin, name);
    }

    cout << "Phone: ";
    getline(cin, phone);

    // Keep asking if the phone is not exactly 11 digits or contains letters
    while (phone.length() != 11 || !all_of(phone.begin(), phone.end(), ::isdigit))
    {
        cout << "11-digit phone: ";
        getline(cin, phone);
    }
}

// This stores a name and phone number directly without asking the user to type.
// Useful when we are loading saved data from a file.
void User::set(string n, string p)
{
    name  = n;
    phone = p;
}

// These simply hand back the stored name and phone number when someone asks for them.
string User::getName()  const { return name; }
string User::getPhone() const { return phone; }
