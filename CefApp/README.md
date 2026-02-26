## 🏗 Project Structure

```text
CefApp/
├─ bin/            # Compiled binaries and runtime output
├─ cef/            # CEF distribution binaries and third-party dependencies
└─ src/
   ├─ app/         # Application lifecycle layer (bootstrap, initialization, shutdown)
   │  ├─ Application.cpp
   │  ├─ Application.h
   │  └─ EntryPoint.cpp      # Win32 entry point (WinMain), delegates to Application
   ├─ cef/          # CEF integration layer
   ├─ platform/
   ├─ resources/
   └─ ui/           # Native window composition layer
      ├─ MainWindow.cpp      # Top-level window, layout & child window orchestration
      ├─ MainWindow.h
      ├─ OverlayWindow.cpp   # Native renderer viewport container (D3D target)
      └─ OverlayWindow.h 
 ```