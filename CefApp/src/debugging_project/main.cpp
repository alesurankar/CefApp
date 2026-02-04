//#include "../platform/WinWrapper.h"
//#include <filesystem>
//#include "include/cef_app.h"
//#include "App.h"
//#include "Window.h"
//
//using namespace std::string_literals;
//
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	const CefMainArgs mainArgs(hInstance);
//	CefRefPtr<CefApp> pApp = new App(); 
//	const int exitCode = CefExecuteProcess(mainArgs, pApp, nullptr);
//	if (exitCode >= 0) {
//		return exitCode;
//	}
//
//	CefSettings settings;
//	settings.multi_threaded_message_loop = true;
//	settings.no_sandbox = true; 
//	CefString(&settings.cache_path).FromString(
//		(std::filesystem::current_path() / "cef_cache"s).string()
//	);
//
//	if (!CefInitialize(mainArgs, settings, pApp, nullptr)) {
//		MessageBoxA(nullptr, "CEF Initialization failed", "Error", MB_ICONERROR);
//		return -1;
//	}
//
//	HWND hWndMain = CreateMainWindow(hInstance);
//	if (!hWndMain)
//	{
//		MessageBoxA(nullptr, "Failed to create browser window", "Error", MB_ICONERROR);
//		CefShutdown();
//		return -1;
//	}
//
//	MSG msg;
//	while (GetMessageA(&msg, nullptr, 0, 0))
//	{
//		TranslateMessage(&msg);
//		DispatchMessageA(&msg);
//	}
//	
//	CleanupMainWindow(hInstance);
//	CefShutdown();
//	
//	return (int)msg.wParam;
//}