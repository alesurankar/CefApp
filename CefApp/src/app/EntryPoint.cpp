#include <app/Application.h>
#include <util/MyException.h>


int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
    try {
        Application app;
        // blocking mode by default
        app.EnableRealTimeLoop(true);
        return app.Run(hInstance, lpCmdLine, nCmdShow);
    }
    catch (...) {
        MessageBox(nullptr, "Fatal error escaped Application", "Critical Error", MB_OK);
        return -1;
    }
}

