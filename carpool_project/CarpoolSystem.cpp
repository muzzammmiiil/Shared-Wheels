#include "CarpoolSystem.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Saves all current carpool rides to carpool.txt.
// Each ride goes on one line with fields separated by the | character.
// This is called every time a ride is added, deleted, or a seat is booked.
void CarpoolSystem::saveFile()
{
    ofstream file("carpool.txt");
    for (int i = 0; i < cnt; i++)
        file << pool[i].getSrc()                     << "|"
             << pool[i].getDst()                     << "|"
             << pool[i].getDepartureTime()           << "|"
             << pool[i].getDriver().getName()        << "|"
             << pool[i].getDriver().getPhone()       << "|"
             << pool[i].getDriver().getSeats()       << "|"
             << pool[i].getDriver().getPrice()       << "|"
             << pool[i].getDriverUsername()          << "|"
             << pool[i].getDriver().getCarModel()    << "|"
             << pool[i].getDriver().getPlateNumber() << "\n";
}

// Reads all carpool rides from carpool.txt into memory.
// Each line is split by | and the pieces are stored into a Carpool object.
// If a line has bad data the try-catch block skips it safely.
void CarpoolSystem::loadFile()
{
    ifstream file("carpool.txt");
    string line;
    cnt = 0;
    while (getline(file, line) && cnt < MAX)
    {
        if (line.empty()) continue;
        stringstream ss(line);
        string src, dst, depTime, name, phone, seats, price, driverUser, cm, pn;
        getline(ss, src,        '|');
        getline(ss, dst,        '|');
        getline(ss, depTime,    '|');
        getline(ss, name,       '|');
        getline(ss, phone,      '|');
        getline(ss, seats,      '|');
        getline(ss, price,      '|');
        getline(ss, driverUser, '|');
        getline(ss, cm,         '|');
        getline(ss, pn);
        try
        {
            pool[cnt].set(src, dst, depTime, name, phone,
                          stoi(seats), stod(price), driverUser, cm, pn);
            cnt++;
        }
        catch (...) {}  // skip any line that cannot be read properly
    }
}

// Reads a number from the keyboard and checks it falls between minVal and maxVal.
// If the input is bad it clears the error and returns false.
bool CarpoolSystem::getChoice(int &choice, int minVal, int maxVal)
{
    cin >> choice;
    if (cin.fail() || choice < minVal || choice > maxVal)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid. Enter " << minVal << "-" << maxVal << ".\n";
        return false;
    }
    cin.ignore(1000, '\n');
    return true;
}

// Asks the user to type a username and password.
// If confirm is true it asks for the password twice so the user does not mistype it.
void CarpoolSystem::getCreds(string &username, string &password, bool confirm)
{
    cout << "Username: ";
    getline(cin, username);
    while (username.empty())
    {
        cout << "Not empty: ";
        getline(cin, username);
    }

    cout << "Password: ";
    getline(cin, password);
    while (password.empty())
    {
        cout << "Not empty: ";
        getline(cin, password);
    }

    if (confirm)
    {
        string c;
        cout << "Confirm Password: ";
        getline(cin, c);
        while (c != password)
        {
            cout << "Passwords don't match. Re-enter Password: ";
            getline(cin, password);
            cout << "Confirm Password: ";
            getline(cin, c);
        }
    }
}

// Checks that a time string is in the correct format HH:MM
// and that the hours are 0-23 and minutes are 0-59
bool CarpoolSystem::isValidTime(const string &t)
{
    if (t.size() != 5)  return false;
    if (!isdigit(t[0])) return false;
    if (!isdigit(t[1])) return false;
    if (t[2] != ':')    return false;
    if (!isdigit(t[3])) return false;
    if (!isdigit(t[4])) return false;
    int hours   = (t[0]-'0')*10 + (t[1]-'0');
    int minutes = (t[3]-'0')*10 + (t[4]-'0');
    return hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59;
}

// Lets a logged-in driver create and add a new carpool ride.
// It pulls the driver's name, phone, car, and plate from their saved account
// so the driver does not have to retype that information every time.
void CarpoolSystem::addCarpool(const string &driverUser)
{
    if (cnt >= MAX) { cout << "Storage full!\n"; return; }

    Account *acc = Auth::getInstance().getDriverAccount(driverUser);
    if (!acc) { cout << "Driver account not found.\n"; return; }

    string src, dst, time;
    cout << "\n-- Carpool Details --\n";

    cout << "Source: ";
    getline(cin, src);
    while (src.empty()) { cout << "Not empty: "; getline(cin, src); }

    cout << "Destination: ";
    getline(cin, dst);
    while (dst.empty()) { cout << "Not empty: "; getline(cin, dst); }

    cout << "Departure Time (HH:MM): ";
    getline(cin, time);
    while (!isValidTime(time))
    {
        cout << "Please enter valid time (HH:MM, 00:00-23:59): ";
        getline(cin, time);
    }

    cout << "Seats: ";
    int seats;
    cin >> seats;
    while (cin.fail() || seats <= 0)
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Must be a number >0: "; cin >> seats;
    }

    cout << "Price/seat: ";
    double price;
    cin >> price;
    while (cin.fail() || price <= 0)
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Must be a number >0: "; cin >> price;
    }
    cin.ignore(1000, '\n');

    // Use the driver's saved account info to fill in name, phone, car, plate
    pool[cnt].set(src, dst, time,
                  acc->getDriverName(), acc->getDriverPhone(),
                  seats, price,
                  driverUser,
                  acc->getCarModel(), acc->getPlateNumber());
    cnt++;
    saveFile();
    cout << "Carpool added!\n";
}

// Prints every single carpool in the system with a number in front
void CarpoolSystem::viewAll()
{
    if (!cnt) { cout << "No carpools.\n"; return; }
    for (int i = 0; i < cnt; i++)
    {
        cout << "\n#" << i + 1 << " ";
        pool[i].display();
    }
}

// Prints only the carpools that belong to the given driver username
void CarpoolSystem::viewMine(const string &username)
{
    int found = 0;
    for (int i = 0; i < cnt; i++)
        if (pool[i].getDriverUsername() == username)
        {
            cout << "\n#" << ++found << " ";
            pool[i].display();
        }
    if (!found) cout << "No carpools added yet.\n";
}

// Lets a driver delete one of their own carpools.
// First shows only their rides, then asks which number to remove.
// After removal it shifts the remaining rides to fill the gap.
void CarpoolSystem::deleteCarpool(const string &username)
{
    // Find the positions of all rides belonging to this driver
    int myIdx[MAX], myCount = 0;
    for (int i = 0; i < cnt; i++)
        if (pool[i].getDriverUsername() == username)
            myIdx[myCount++] = i;

    if (!myCount) { cout << "No carpools to delete.\n"; return; }

    // Show the driver's rides so they can pick which one to delete
    for (int i = 0; i < myCount; i++)
    {
        cout << "\n#" << i + 1 << " ";
        pool[myIdx[i]].display();
    }

    cout << "\nEnter carpool number to delete (1-" << myCount << "): ";
    int pick;
    cin >> pick;
    while (cin.fail() || pick < 1 || pick > myCount)
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid, enter 1-" << myCount << ": "; cin >> pick;
    }
    cin.ignore(1000, '\n');

    // Shift all rides after the deleted one one position to the left
    int delIdx = myIdx[pick - 1];
    for (int i = delIdx; i < cnt - 1; i++)
        pool[i] = pool[i + 1];
    cnt--;
    saveFile();
    cout << "Carpool deleted.\n";
}

// Lets anyone search for rides by typing a source and destination.
// Shows all matching rides including ones that are fully booked.
void CarpoolSystem::search()
{
    string src, dst;
    cout << "Source: ";      getline(cin, src);
    cout << "Destination: "; getline(cin, dst);

    bool found = false;
    for (int i = 0; i < cnt; i++)
    {
        if (toLower(pool[i].getSrc()) == toLower(src) &&
            toLower(pool[i].getDst()) == toLower(dst))
        {
            cout << "\n";
            pool[i].display();
            if (pool[i].getDriver().getSeats() == 0)
                cout << "*** FULLY BOOKED ***\n";
            found = true;
        }
    }
    if (!found) cout << "No carpool found for this route.\n";
}

// Lets a logged-in passenger book a seat on a ride.
// Only shows rides that still have at least one seat available.
// After booking, the seat count is reduced by one and the file is updated.
void CarpoolSystem::bookSeat(Passenger &passenger)
{
    string src, dst;
    cout << "Source: ";      getline(cin, src);
    cout << "Destination: "; getline(cin, dst);

    // Collect all rides on this route that still have seats
    int matches[MAX], matchCount = 0;
    for (int i = 0; i < cnt; i++)
        if (toLower(pool[i].getSrc()) == toLower(src) &&
            toLower(pool[i].getDst()) == toLower(dst) &&
            pool[i].getDriver().getSeats() > 0)
        {
            cout << ++matchCount << ". ";
            pool[i].displayWithCar();
            matches[matchCount - 1] = i;
        }

    if (!matchCount) { cout << "None available.\n"; return; }

    cout << "Pick (1-" << matchCount << "): ";
    int pick;
    cin >> pick;
    while (cin.fail() || pick < 1 || pick > matchCount)
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Invalid, enter 1-" << matchCount << ": "; cin >> pick;
    }
    cin.ignore(1000, '\n');

    int idx = matches[pick - 1];

    // Do not let the passenger book the same route twice in one session
    if (passenger.getBookedSrc() == pool[idx].getSrc() &&
        passenger.getBookedDst() == pool[idx].getDst())
    {
        cout << "You already booked this route!\n";
        return;
    }

    // Reduce available seats by one and save the booking
    pool[idx].getDriver().setSeats(pool[idx].getDriver().getSeats() - 1);
    passenger.setBooking(pool[idx].getSrc(), pool[idx].getDst());
    cout << "Booked! Please call the driver for Confirmation\n";
    passenger.display();
    saveFile();
}

// This is the slide-through browsing feature for passengers.
// The passenger can press N to see the next ride, P for previous,
// B to book the current ride, or Q to quit the browser.
void CarpoolSystem::slider(Passenger &passenger)
{
    // Build a list of only the rides that still have seats available
    int available[MAX], availableCount = 0;
    for (int i = 0; i < cnt; i++)
        if (pool[i].getDriver().getSeats() > 0)
            available[availableCount++] = i;

    if (!availableCount)
    {
        if (cnt == 0) cout << "No carpools exist yet.\n";
        else          cout << "All carpools are fully booked.\n";
        return;
    }

    int cur = 0;
    char ch;
    while (true)
    {
        // Show which ride we are currently viewing out of the total available
        cout << "\n+====== RIDE [" << cur + 1 << "/" << availableCount << "] ======+\n";
        pool[available[cur]].display();
        cout << "[N]ext [P]rev [B]ook [Q]uit: ";
        cin >> ch; ch = tolower(ch); cin.ignore(1000, '\n');

        if (ch == 'n')
        {
            if (cur < availableCount - 1) cur++;
            else cout << "Last ride.\n";
        }
        else if (ch == 'p')
        {
            if (cur > 0) cur--;
            else cout << "First ride.\n";
        }
        else if (ch == 'b')
        {
            int idx = available[cur];
            if (passenger.getBookedSrc() == pool[idx].getSrc() &&
                passenger.getBookedDst() == pool[idx].getDst())
            {
                cout << "You already booked this route!\n";
            }
            else
            {
                // Book the ride and save
                pool[idx].getDriver().setSeats(pool[idx].getDriver().getSeats() - 1);
                passenger.setBooking(pool[idx].getSrc(), pool[idx].getDst());
                cout << "Booked! Please call the driver for Confirmation\n";
                passenger.display();
                saveFile();
            }

            // Refresh the available list since one seat was just taken
            availableCount = 0;
            for (int i = 0; i < cnt; i++)
                if (pool[i].getDriver().getSeats() > 0)
                    available[availableCount++] = i;

            if (!availableCount) { cout << "No more rides.\n"; break; }
            if (cur >= availableCount) cur = availableCount - 1;
        }
        else if (ch == 'q')
        {
            cout << "Exiting slider.\n";
            break;
        }
        else cout << "Use N/P/B/Q.\n";
    }
}

// Shows the driver section of the program.
// The driver can register a new account or log into an existing one.
// After logging in they can add rides, view their rides, or delete a ride.
void CarpoolSystem::driverPortal()
{
    cout << "\n[DRIVER] 1.Register 2.Login 0.Back: ";
    int choice;
    if (!getChoice(choice, 0, 2)) return;
    if (choice == 0) return;

    string username, password;
    if (choice == 1)
    {
        // Registration: get credentials and then personal and vehicle details
        getCreds(username, password, true);
        cout << "Registered! Logging you in...\n";
        cout << "\n-- Driver & Vehicle Details --\n";

        string driverName, driverPhone, carModel, plateNumber;

        cout << "Name: "; getline(cin, driverName);
        while (driverName.empty()) { cout << "Not empty: "; getline(cin, driverName); }

        cout << "Phone: "; getline(cin, driverPhone);
        while (driverPhone.length() != 11 ||
               !all_of(driverPhone.begin(), driverPhone.end(), ::isdigit))
        {
            cout << "11-digit phone: "; getline(cin, driverPhone);
        }

        cout << "Car/Bike Model: "; getline(cin, carModel);
        while (carModel.empty()) { cout << "Not empty: "; getline(cin, carModel); }

        cout << "Plate Number: "; getline(cin, plateNumber);
        while (plateNumber.empty()) { cout << "Not empty: "; getline(cin, plateNumber); }

        if (!Auth::getInstance().regDriver(username, password,
                                           driverName, driverPhone,
                                           carModel, plateNumber))
        {
            cout << "Username taken.\n"; return;
        }
    }
    else
    {
        // Login: just check username and password
        getCreds(username, password);
        if (!Auth::getInstance().loginDriver(username, password))
        {
            cout << "Wrong credentials.\n"; return;
        }
    }

    cout << "Welcome, Driver " << username << "!\n";
    int ch = -1;
    do
    {
        cout << "\n[DRIVER] 1.Add Carpool  2.My Carpools  3.Delete Carpool  0.Logout: ";
        cin >> ch;
        if (cin.fail()) { cin.clear(); cin.ignore(1000,'\n'); ch = -1; continue; }
        cin.ignore(1000, '\n');
        if      (ch == 1) addCarpool(username);
        else if (ch == 2) viewMine(username);
        else if (ch == 3) deleteCarpool(username);
        else if (ch != 0) cout << "Invalid.\n";
    } while (ch != 0);

    cout << "Logged out.\n";
}

// Shows the passenger section of the program.
// The passenger can register or log in, then browse or book rides.
void CarpoolSystem::passPortal()
{
    cout << "\n[PASSENGER] 1.Register 2.Login 0.Back: ";
    int choice;
    if (!getChoice(choice, 0, 2)) return;
    if (choice == 0) return;

    string username, password;
    getCreds(username, password, choice == 1);

    if (choice == 1)
    {
        string ph;
        cout << "Phone: "; getline(cin, ph);
        while (ph.length() != 11 || !all_of(ph.begin(), ph.end(), ::isdigit))
        {
            cout << "11-digit phone: "; getline(cin, ph);
        }
        if (!Auth::getInstance().regPass(username, password, ph))
        {
            cout << "Username taken.\n"; return;
        }
        cout << "Registered! Logging you in...\n";
    }
    else if (!Auth::getInstance().loginPass(username, password))
    {
        cout << "Wrong credentials.\n"; return;
    }

    cout << "Welcome, Passenger " << username << "!\n";

    // Create a Passenger object for this session and load their phone from the account
    Passenger passenger;
    passenger.set(username, Auth::getInstance().getPassPhone(username));

    int ch = -1;
    do
    {
        cout << "\n[PASSENGER] 1.Slide Rides  2.Book  0.Logout: ";
        cin >> ch;
        if (cin.fail()) { cin.clear(); cin.ignore(1000,'\n'); ch = -1; continue; }
        cin.ignore(1000, '\n');
        if      (ch == 1) slider(passenger);
        else if (ch == 2) bookSeat(passenger);
        else if (ch != 0) cout << "Invalid.\n";
    } while (ch != 0);

    cout << "Logged out.\n";
}

// When CarpoolSystem is first created it loads all saved rides from the file
CarpoolSystem::CarpoolSystem() : cnt(0) { loadFile(); }

// Returns the one and only CarpoolSystem object
CarpoolSystem &CarpoolSystem::getInstance()
{
    static CarpoolSystem instance;
    return instance;
}

// The main menu loop. Runs until the user chooses to exit.
// From here the user picks whether they are a driver or a passenger.
void CarpoolSystem::menu()
{
    int role = -1;
    do
    {
        cout << "\n===== CARPOOL SYSTEM =====\n1.Driver  2.Passenger  0.Exit\nRole: ";
        cin >> role;
        if (cin.fail()) { cin.clear(); cin.ignore(1000,'\n'); role = -1; continue; }
        cin.ignore(1000, '\n');
        if      (role == 1) driverPortal();
        else if (role == 2) passPortal();
        else if (role != 0) cout << "Invalid.\n";
    } while (role != 0);
    cout << "Goodbye!\n";
}
