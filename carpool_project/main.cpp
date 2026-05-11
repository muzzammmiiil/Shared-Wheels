#include "CarpoolFacade.h"

// This is the body of the CarpoolFacade start function.
// All it does is ask the CarpoolSystem to show its main menu.
void CarpoolFacade::start()
{
    CarpoolSystem::getInstance().menu();
}

// This is where the program begins.
// We create a CarpoolFacade object and call start().
// That one call kicks off the entire carpool system.
int main()
{
    CarpoolFacade app;
    app.start();
    return 0;
}
