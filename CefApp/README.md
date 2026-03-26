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
   │  ├─ shaders/     # HLSL files
   │  ├─ bindables/
   │  │  ├─ BindableBase.h    # includes all concrete bindables
   │  │  ├─ Bindable          # abstract base class
   │  │  ├─ ConstantBuffers
   │  │  ├─ IndexBuffer
   │  │  ├─ InputLayout
   │  │  ├─ PixelShader
   │  │  ├─ Topology
   │  │  ├─ TransformCbuf
   │  │  ├─ VertexBuffer     
   │  │  └─ VertexShader    
   │  ├─ Graphics
   │  └─ RendererWindow
   ├─ resources/
   ├─ ui/           # Native window composition layer
   │   ├─ BrowserView     # Cef Browser
   │   ├─ D3DRenderer
   │   ├─ MainWindow      # Top-level window
   │   └─ WindowTitleBar
   └─ util/
       ├─ AppException
       ├─ GraphicsThrowMacros
       └─ MyException
 ```