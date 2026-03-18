## 🏗 Project Structure

The ReactCef frontend provides the UI layer of the application using React, Vite, and TailwindCSS.
It runs inside the embedded Chromium browser provided by CEF and communicates with the native C++ backend.

```text
ReactCef/
├─ public/
├─ src/
│  ├─ cef/
│  │  └─ cefInterface.ts
│  ├─ hooks/
│  │  ├─ dropdownManager.ts
│  │  └─ viewManager.ts
│  ├─ ui/
│  │  ├─ bodyContainer/
│  │  │  ├─ frames/
│  │  │  │  ├─ BaseFrame.tsx
│  │  │  │  ├─ D3DFrame.tsx
│  │  │  │  └─ EmptyFrame.tsx
│  │  │  ├─ BodyContainer.tsx
│  │  │  ├─ MainFrameArea.tsx
│  │  │  └─ NavigationBar.tsx
│  │  ├─ icons/
│  │  │  ├─ svg/
│  │  │  ├─ Icon.tsx
│  │  │  └─ IconPaths.ts
│  │  ├─ overlayLayer/
│  │  │  ├─ dropdowns/
│  │  │  │  ├─ BaseDropdown.tsx
│  │  │  │  ├─ OtherDropdown.tsx
│  │  │  │  └─ ViewPanelDropdown.tsx
│  │  │  └─ OverlayLayer.tsx
│  │  ├─ titleBar/
│  │  │  ├─ TabContainer.tsx
│  │  │  ├─ TitleBar.tsx
│  │  │  ├─ ViewButton.tsx
│  │  │  └─ WindowControls.tsx
│  │  └─ FooterBar.tsx
│  ├─ utils/
│  ├─ App.tsx
│  ├─ index.css
│  └─ main.tsx    # wrapper for root
└─ index.html     # Entry
 ```