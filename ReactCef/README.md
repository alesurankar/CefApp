## 🏗 Project Structure

The ReactCef frontend provides the UI layer of the application using React, Vite, and TailwindCSS.
It runs inside the embedded Chromium browser provided by CEF and communicates with the native C++ backend.

```text
ReactCef/
├─ public/
├─ src/
│  ├─ cef/
│  │  └─ cefInterface.ts
│  ├─ gui/
│  │  ├─ frames/
│  │  │  └─ BaseFrame.tsx
│  │  ├─ titleBar/
│  │  │  ├─ TabContainer.tsx
│  │  │  ├─ TitleBar.tsx
│  │  │  └─ WindowControls.tsx
│  │  ├─ BodyContainer.tsx
│  │  └─ FooterBar.tsx
│  ├─ utils/
│  ├─ App.tsx
│  ├─ index.css
│  └─ main.tsx    # wrapper for root
└─ index.html     # Entry
 ```