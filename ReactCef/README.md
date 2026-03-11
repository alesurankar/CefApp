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
│  │  ├─ BodyContainer.tsx
│  │  ├─ FooterBar.tsx
│  │  └─ TitleBar.tsx
│  ├─ utils/
│  ├─ App.tsx
│  ├─ index.css
│  └─ main.tsx    # wrapper for root
└─ index.html     # Entry
 ```