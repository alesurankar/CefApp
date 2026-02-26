#pragma once
#include "../platform/MyWin.h"

class Application {
public:
	Application() = default;
	~Application() = default;
	int Run(HINSTANCE hInstance);
	void EnableRealTimeLoop(bool enable) { useRealTimeLoop_ = enable; }
private:
	bool Initialize(HINSTANCE hInstance);
	int RunMessageLoop();
	int RunRealTimeLoop();
	int RunBlockingLoop();
	void Shutdown();
private:
	HINSTANCE hInstance_ = nullptr;
	HWND mainWindow_ = nullptr;
	bool running_ = false;
	bool useRealTimeLoop_ = false;
};