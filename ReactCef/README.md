## 🏗 Project Structure

The ReactCef frontend provides the UI layer of the application using React, Vite, and TailwindCSS.
It runs inside the embedded Chromium browser provided by CEF and communicates with the native C++ backend.

```text
ReactCef/
├─ public/
├─ src/
│  ├─ cef/
│  │  └─ cefInterface.ts
│  ├─ frames/
│  │  └─ BaseFrame.tsx
│  ├─ gui/
│  │  ├─ bodyContainer/
│  │  │  ├─ BodyContainer.tsx
│  │  │  ├─ MainFrameArea.tsx
│  │  │  └─ NavigationBar.tsx
│  │  ├─ dropdown/
│  │  │  └─ DropdownWindow.tsx
│  │  ├─ overlays/
│  │  │  └─ OverlayLayer.tsx
│  │  ├─ titleBar/
│  │  │  ├─ TabContainer.tsx
│  │  │  ├─ TitleBar.tsx
│  │  │  ├─ ViewButton.tsx
│  │  │  └─ WindowControls.tsx
│  │  └─ FooterBar.tsx
│  ├─ hooks/
│  │  └─ tabManager.ts
│  ├─ icons/
│  │  ├─ svg/
│  │  ├─ Icon.tsx
│  │  └─ IconPaths.ts
│  ├─ utils/
│  ├─ App.tsx
│  ├─ index.css
│  └─ main.tsx    # wrapper for root
└─ index.html     # Entry
 ```