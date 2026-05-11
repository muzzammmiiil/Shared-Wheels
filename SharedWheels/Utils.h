#pragma once
#include <string>
#include <algorithm>
using namespace std;

// This file has one small helper function used across the whole project.
// Its job is to convert any word to all lowercase letters.
// For example "Karachi" becomes "karachi" and "KARACHI" also becomes "karachi".
// We do this so that when we compare two city names, capital letters do not cause a mismatch.

string toLower(string s);
