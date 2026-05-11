#pragma once
#include "Utils.h"
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

// This file defines a template class called Repository.
// A template class is a class that works with any data type you give it.
// For example Repository<Driver> would manage a list of drivers,
// and Repository<Passenger> would manage a list of passengers.
// Think of it like a smart filing cabinet that can hold any kind of records.

template <typename T>
class Repository
{
    // The actual list of items stored in this repository
    vector<T> items;

    // A map that links each item's name to its position in the list.
    // This makes searching by name very fast without looping through everything.
    map<string, int> idx;

    // Rebuilds the name-to-position map after an item is added or removed.
    // We need this because positions shift when something is deleted.
    void reindex()
    {
        idx.clear();
        for (int i = 0; i < (int)items.size(); ++i)
            idx[toLower(items[i].getName())] = i;
    }

public:
    // Adds a new item to the list.
    // Returns false if an item with the same name already exists.
    bool add(const T &v)
    {
        string k = toLower(v.getName());
        if (idx.count(k)) return false;
        idx[k] = (int)items.size();
        items.push_back(v);
        return true;
    }

    // Removes an item by name.
    // Returns false if no item with that name was found.
    bool remove(const string &n)
    {
        auto it = idx.find(toLower(n));
        if (it == idx.end()) return false;
        items.erase(items.begin() + it->second);
        reindex();
        return true;
    }

    // Finds and returns a pointer to an item by its name.
    // Returns nullptr if nothing was found.
    T *find(const string &n)
    {
        auto it = idx.find(toLower(n));
        return it == idx.end() ? nullptr : &items[it->second];
    }

    // Returns the full list of all items
    const vector<T> &getAll() const { return items; }

    // Returns how many items are currently stored
    int size() const { return (int)items.size(); }

    // Sorts all items using a comparison rule you provide.
    // For example you could sort drivers by price or by name.
    template<typename Cmp>
    void sortBy(Cmp c)
    {
        sort(items.begin(), items.end(), c);
        reindex();
    }

    // Returns a new list containing only items that match a condition you provide.
    // For example you could filter to get only drivers with more than 2 seats.
    template<typename Pred>
    vector<T> filter(Pred p) const
    {
        vector<T> r;
        auto it = items.begin();
        while ((it = find_if(it, items.end(), p)) != items.end())
            r.push_back(*it++);
        return r;
    }
};

// Searches a plain vector for an item with a matching name.
// This works outside the Repository class for any vector of objects.
template<typename T>
const T *findByName(const vector<T> &col, const string &name)
{
    auto it = find_if(col.begin(), col.end(),
        [&](const T &x){ return toLower(x.getName()) == toLower(name); });
    return it != col.end() ? &(*it) : nullptr;
}

// Prints every item in a vector with a numbered label.
// An optional heading can be shown at the top.
template<typename T>
void displayAll(const vector<T> &col, const string &hdr = "")
{
    if (!hdr.empty()) cout << "\n--- " << hdr << " ---\n";
    if (col.empty())  { cout << "(none)\n"; return; }
    int i = 1;
    for (const T &x : col) { cout << "#" << i++ << " "; x.display(); }
}

// Returns a sorted copy of a vector without changing the original.
// Useful when you want to display items in a different order temporarily.
template<typename T, typename Cmp>
vector<T> sortedCopy(const vector<T> &col, Cmp c)
{
    vector<T> r = col;
    sort(r.begin(), r.end(), c);
    return r;
}
