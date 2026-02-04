#include "../platform/WinWrapper.h"
#include <filesystem>
#include "../cef/MyCefApp.h"
#include "../ui/MainWindow.h"

using namespace std::string_literals;

// Step 0: App is launched
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Step 1: Handle CEF child processes
	const CefMainArgs mainArgs(hInstance);
	CefRefPtr<CefApp> pApp = new MyCefApp();
	// ensures child processes never execute WinMain app logic.
	const int exitCode = CefExecuteProcess(mainArgs, pApp, nullptr);
	if (exitCode >= 0) {
		return exitCode;
	}

	// Step 2: Initialize CEF in the browser process
	CefSettings settings;
	settings.multi_threaded_message_loop = true;
	settings.no_sandbox = true;
	CefString(&settings.cache_path).FromString(
		(std::filesystem::current_path() / "cef_cache"s).string()
	);

	if (!CefInitialize(mainArgs, settings, pApp, nullptr)) {
		MessageBoxA(nullptr, "CEF Initialization failed", "Error", MB_ICONERROR);
		return -1;
	}

	// Step 4: Create Win32 window + browser
	HWND hWndMain = CreateMainWindow(hInstance);
	if (!hWndMain)
	{
		MessageBoxA(nullptr, "Failed to create browser window", "Error", MB_ICONERROR);
		CefShutdown();
		return -1;
	}

	// Step 11: Win32 message loop
	MSG msg;
	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	OutputDebugStringA("CEF: Shutdown\n");
	CleanupMainWindow(hInstance);
	CefShutdown();

	return (int)msg.wParam;
}