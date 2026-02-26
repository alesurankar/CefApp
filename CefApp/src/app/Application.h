#pragma once
#include "../platform/MyWin.h"

class Application {
public:
	Application() = default;
	~Application() = default;
	int Run(HINSTANCE hInstance);
private:
	bool Initialize(HINSTANCE hInstance);
	int RunMessageLoop();
	void Shutdown();
private:
	HINSTANCE hInstance_ = nullptr;
	HWND mainWindow_ = nullptr;
	bool running_ = false;
};