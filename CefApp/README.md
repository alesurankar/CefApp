## 🏗 Project Structure

```text
CefApp/
├─ bin/            # Compiled binaries and runtime output
├─ cef_lib/        # CEF distribution binaries and third-party dependencies
└─ src/
   ├─ app/         # Application lifecycle layer (bootstrap, initialization, shutdown)
   │  ├─ Application
   │  └─ EntryPoint.cpp      # Win32 entry point (WinMain), delegates to Application
   │
   ├─ cef/          # CEF integration layer
   │   ├─ config/
   │   ├─ MyCefApp
   │   └─ MyCefClient
   │ 
   ├─ platform/
   │   ├─ MyMath
   │   ├─ MyTimer
   │   ├─ MyWin
   │   └─ MyWinX 
   │
   ├─ renderer/
   │
   ├─ resources/
   │
   ├─ ui/           # Native window composition layer
   │   ├─ BrowserView     # Cef Browser
   │   ├─ D3DRenderer
   │   ├─ MainWindow      # Top-level window
   │   └─ WindowTitleBar
   │
   └─ util/
       ├─ AppException
       ├─ AppThrowMacros
       ├─ DebugLog
       ├─ DxginfoManager
       ├─ GraphicsThrowMacros
       ├─ MyException
       └─ WindowsThrowMacros 
```


```text
renderer/
├─ bindables/         # GPU resources
│   ├─ BindableBase.h    # includes all concrete bindables
│   ├─ Bindable          # abstract base class
│   ├─ ConstantBuffers
│   ├─ IndexBuffer
│   ├─ InputLayout
│   ├─ PixelShader
│   ├─ Topology
│   ├─ TransformCbuf
│   ├─ VertexBuffer     
│   └─ VertexShader    
│
├─ drawables/     # renderable objects
│   ├─ Box            # semantic object
│   ├─ Drawable       # abstract base class 
│   └─ DrawableBase   # Shared Resource Cache
│
├─ geometry/        # CPU mesh data
│   ├─ Cone         # Procedural Mesh Generator
│   ├─ Cube         # Static Mesh Generator
│   ├─ IndexedTriangleList    # Mesh Data Container
│   ├─ Plane        # Tessellated Grid Mesh Generator
│   ├─ Prism        # Extruded Polygon Mesh Generator
│   └─ Sphere       # Tesselated Sphere Generator
│
├─ input/
│   ├─ Keyboard
│   └─ Mouse
│
├─ shaders/     # HLSL files
├─ Graphics
└─ RendererWindow
```