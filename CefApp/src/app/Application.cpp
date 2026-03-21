#include "Application.h"
//#include <cef/MyCefApp.h>
#include <util/AppException.h>
#include <filesystem>


int Application::Run(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInstance_ = hInstance;

    const CefMainArgs mainArgs(hInstance_);
    cefApp_ = new MyCefApp();

    int exitCode = CefExecuteProcess(mainArgs, cefApp_, nullptr);
    if (exitCode >= 0) {
        return exitCode;
    }

    try {
        Initialize();
        int code = RunMessageLoop();
        Shutdown();
        return code;
    }
    catch (...) {
        Shutdown();
        throw;
    }
}

void Application::Initialize()
{
    CefSettings settings;
    settings.multi_threaded_message_loop = true;
    settings.no_sandbox = true;

    CefString(&settings.cache_path).FromString(
        (std::filesystem::current_path() / "cef_cache").string()
    );

    if (!CefInitialize(CefMainArgs(hInstance_), settings, cefApp_, nullptr)) {
        throw AppException(__LINE__, __FILE__, "CEF Initialization failed");
    }

    mainWnd_ = std::make_unique<MainWindow>();
    if (!mainWnd_) {
        throw AppException(__LINE__, __FILE__, "Failed to create main window");
    }
    running_ = true;
}

int Application::RunMessageLoop()
{
    return useRealTimeLoop_ ? RunRealTimeLoop() : RunBlockingLoop();
}

int Application::RunRealTimeLoop()
{
    MSG msg{};

    while (running_) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running_ = false; 
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Render the overlay
        if (mainWnd_->GetOverlay()) {
            mainWnd_->GetOverlay()->Render();
        }
    }

    return static_cast<int>(msg.wParam);
}

int Application::RunBlockingLoop()
{
    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

void Application::Shutdown()
{
    running_ = false;
    mainWnd_.reset();
    CefShutdown();
}
