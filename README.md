# CefApp

A CEF-based desktop application under development.  

The final goal of this project is not fully defined yet, but the idea is to combine **modern UI with a native 3D renderer**, creating a flexible framework that could evolve into a game engine inspired by **Unreal Engine**, with a CEF-powered GUI. 

---

## 🏗 Architecture

The application consists of three main components:

### 1. Main Window
- A Win32 window that serves as the parent for all other windows and widgets  
- Manages window resizing, focus, and message routing  

### 2. Renderer Widget (Independent)
- A native child window of the main window  
- Handles **real-time 3D rendering** (D3D11 planned)  
- Fully independent of CEF, ensuring **native GPU performance**  

### 3. CEF / React GUI Panels
- Embedded Chromium browser for **dynamic UI**  
- Provides **dockable panels, buttons, sliders, menus**, and other controls  
- Overlays the renderer widget when necessary  
- Sends events/messages to the C++ backend to control widgets, rendering, or other behaviors  

---

## ⬇️ Download / Setup

CEF binaries can be downloaded from the official page:  
[https://cef-builds.spotifycdn.com/index.html](https://cef-builds.spotifycdn.com/index.html)

Setup follows a minimal distribution approach, inspired by this YouTube tutorial:  
[C++ Nano CEF - ChiliTomatoNoodle](https://www.youtube.com/watch?v=Enio6T3DunA&list=PLqCJpWy5Fohc_Xz5nV0efhzaVbtJu07aa)

---

## 🛠 Tech Stack

- **Chromium Embedded Framework (CEF)** – UI panels  
- **C++ / Win32 API** – main window & backend logic  
- **React + Tailwind CSS** – interactive GUI  
- **Direct3D 11** – renderer widget (planned for 3D viewport)

---

## 🚧 Current Status

- Main window and CEF panels working  
- Renderer widget scaffold implemented (no full 3D yet)  
- Communication between UI and backend functioning  
- Multiple widgets under development  

---

## 🎯 Features / Goals

- Modular editor-style architecture  
- Custom window overlays and input handling  
- Multiple interactive widgets under development  
- Planned D3D11 renderer for 3D content  
- Communication between CEF UI and native widgets  

> Note: This is an experimental project and primarily a playground for advanced CEF + Win32 + React integration.

---

## 📌 Future Plans

- Complete D3D11 renderer widget  
- Add more interactive widgets (properties, panels, inspectors)  
- Modular architecture for engine-like flexibility  
- Dynamic UI and animations  
- Optimization and possible cross-platform considerations  

---

## Links

- [CefApp](./CefApp/README.md) – Cef Backend
- [ReactCef](./ReactCef/README.md) – React + Vite Frontend
