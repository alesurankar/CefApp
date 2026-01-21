#include "MyWin.h"
#include <filesystem>
#include "NanoCefApp.h"
#include "NanoBrowserWindow.h"

using namespace std::string_literals;

// Step 0: App is launched
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Step 1: Handle CEF child processes
	const CefMainArgs mainArgs(hInstance);
	CefRefPtr<CefApp> pApp = new NanoCefApp();
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

	CleanupMainWindow(hInstance);
	CefShutdown();

	return (int)msg.wParam;
}

// 1. WinMain(browser process)
//
// 2. CefExecuteProcess() -> exits early if child
//
// 3. CefInitialize() -> starts Chromium threads
//
// 4. NanoCefApp::OnContextInitialized() -> registers scheme
//
// 5. CreateBrowserWindow() -> creates Win32 HWND
//
// 6. WM_CREATE -> create NanoCefClient + CreateBrowser()
//
// 7. Chromium async -> spawns renderer process
//
// 8. NanoCefClient::OnAfterCreated() -> browser HWND ready
//
// 9. Renderer process -> OnContextCreated() -> inject JS functions
//
// 10. Chromium asks for resources -> NanoFileSchemeHandlerFactory -> NanoFileResourceHandler
//
// 11. JS calls -> NanoCefApp::Execute() -> async task -> resolve / reject callbacks
//
// 12. Win32 message loop handles input, resize, close
//
// 13. App quits -> cleanup -> CefShutdown()