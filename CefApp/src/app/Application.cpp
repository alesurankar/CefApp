#include "Application.h"

#include "../cef/MyCefApp.h"
#include "../ui/MainWindow.h"

#include <filesystem>

int Application::Run(HINSTANCE hInstance)
{
    if (!Initialize(hInstance))
        return -1;
    int exitCode = RunMessageLoop();
    Shutdown();

    return exitCode;
}

bool Application::Initialize(HINSTANCE hInstance)
{
    hInstance_ = hInstance;

    // ---------------------------
    // 1. Handle CEF child process
    // ---------------------------
    const CefMainArgs mainArgs(hInstance_);
    CefRefPtr<CefApp> cefApp = new MyCefApp();

    int exitCode = CefExecuteProcess(mainArgs, cefApp, nullptr);
    if (exitCode >= 0)
        return false; // child process exits here

    // ---------------------------
    // 2. Initialize CEF
    // ---------------------------
    CefSettings settings;
    settings.multi_threaded_message_loop = true;
    settings.no_sandbox = true;

    CefString(&settings.cache_path).FromString(
        (std::filesystem::current_path() / "cef_cache").string()
    );

    if (!CefInitialize(mainArgs, settings, cefApp, nullptr))
    {
        MessageBoxA(nullptr, "CEF Initialization failed", "Error", MB_ICONERROR);
        return false;
    }

    // ---------------------------
    // 3. Create Main Window
    // ---------------------------
    mainWindow_ = CreateMainWindow(hInstance_);
    if (!mainWindow_)
    {
        MessageBoxA(nullptr, "Failed to create main window", "Error", MB_ICONERROR);
        return false;
    }
    running_ = true;

    return true;
}

int Application::RunMessageLoop()
{
    if (useRealTimeLoop_)
        return RunRealTimeLoop();
    else
        return RunBlockingLoop();
}

int Application::RunRealTimeLoop()
{
    MSG msg;
    bool running = true;

    while (running)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                running = false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Engine tick goes here
        // EngineCore::Get().Tick();

        Sleep(1); // prevent 100% CPU in early phase
    }

    return static_cast<int>(msg.wParam);
}

int Application::RunBlockingLoop()
{
    MSG msg{};
    while (GetMessageA(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

void Application::Shutdown()
{
    running_ = false;
    CleanupMainWindow(hInstance_);
    CefShutdown();
}
