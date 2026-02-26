#include "Application.h"

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int)
{
    Application app; 
    // blocking mode by default
    app.EnableRealTimeLoop(false);
    return app.Run(hInstance);
}

