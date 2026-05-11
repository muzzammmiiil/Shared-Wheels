#pragma once
#include "CarpoolSystem.h"

// This file defines the CarpoolFacade class.
// A Facade is a design pattern that hides complicated code behind one simple function.
// Instead of calling CarpoolSystem directly in main, we call facade.start().
// Think of it like a power button: you press one button and the whole machine starts.
// You do not need to know what is happening inside.

class CarpoolFacade
{
public:
    // This one function starts the entire program.
    // It simply calls the menu of CarpoolSystem which handles everything from there.
    void start();
};
