#include "Utils.h"

// This is the actual code for the toLower function declared in Utils.h.
// It goes through every letter in the word one by one and makes it lowercase.
// The transform function from the standard library does the heavy lifting here.

string toLower(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
