#pragma once
#include <platform/MyWin.h>
#include <memory>
#include <ui/MainWindow.h>
#include <cef/MyCefApp.h>


class Application 
{
public:
	Application() = default;
	~Application() = default;
	int Run(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);
	void EnableRealTimeLoop(bool enable) { useRealTimeLoop_ = enable; }
private:
	void Initialize();
	int RunMessageLoop();
	int RunRealTimeLoop();
	int RunBlockingLoop();
	void Shutdown();
private:
	std::unique_ptr<MainWindow> mainWnd_;
	HINSTANCE hInstance_ = nullptr;
	bool running_ = false;
	bool useRealTimeLoop_ = false; 
	CefRefPtr<MyCefApp> cefApp_;
};