## 🏗 Project Structure

```text
CefApp/
├─ bin/            # Compiled binaries and runtime output
├─ cef_lib/        # CEF distribution binaries and third-party dependencies
└─ src/
   ├─ app/         # Application lifecycle layer (bootstrap, initialization, shutdown)
   │  ├─ Application
   │  └─ EntryPoint.cpp      # Win32 entry point (WinMain), delegates to Application
   ├─ cef/          # CEF integration layer
   ├─ platform/
   ├─ renderer/
   │  ├─ input/
   │  │   ├─ Keyboard
   │  │   └─ Mouse
   │  ├─ RendererApp
   │  ├─ Graphics
   │  └─ OverlayWindow   # Native renderer viewport container (D3D target)
   ├─ resources/
   └─ ui/           # Native window composition layer
      └─ MainWindow      # Top-level window, layout & child window orchestration
       
 ```