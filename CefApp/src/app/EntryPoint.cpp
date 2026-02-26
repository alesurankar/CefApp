#include "Application.h"

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int)
{
    Application app;
    return app.Run(hInstance);
}

