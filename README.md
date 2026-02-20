# CefApp

A CEF-based desktop application under development.  

The final goal of this project is not fully defined yet, but the idea is to create something inspired by **Unreal Engine** — not as optimized, but with a similar look and interactive behavior.  

Currently, the app includes multiple widgets, one of which will be a **D3D11 renderer**, making it possible that this could evolve into a **game engine with a CEF-based GUI**.

---

## ?? Features / Goals

- Chromium Embedded Framework (CEF) GUI integration  
- Win32 main window with custom overlays  
- Multiple widgets (under development)  
- Planned D3D11 renderer for 3D graphics  
- Dynamic window and input handling  

> Note: The project is experimental and primarily a playground for learning advanced CEF + Win32 + React integration.

---

## ?? Download / Setup

CEF binaries can be downloaded from the official page:  
[https://cef-builds.spotifycdn.com/index.html](https://cef-builds.spotifycdn.com/index.html)

### Minimal distribution approach

The project uses a **minimal CEF distribution**. The initial setup follows this YouTube tutorial:  
[CEF C++ Minimal Setup Tutorial](https://www.youtube.com/watch?v=Enio6T3DunA&list=PLqCJpWy5Fohc_Xz5nV0efhzaVbtJu07aa)

> Make sure to follow the tutorial steps to correctly link CEF with your C++ project.

---

## ?? Tech Stack

- **Chromium Embedded Framework (CEF)**  
- **C++** (Win32 API)  
- **React** (frontend UI)  
- **Tailwind CSS** (styling)  
- **Direct3D 11** (planned 3D rendering)  

---

## ?? Current Status

- Core application structure is implemented  
- Custom windows, overlays, and input handling working  
- Multiple widgets under development  
- Planning to integrate D3D11 renderer for 3D content  

---

## ?? Future Plans

- Full widget ecosystem similar to Unreal Engine  
- Dynamic UI interactions  
- 3D rendering integration with D3D11  
- Modular architecture for future engine-like capabilities  
- Optimization and cross-platform considerations  

---

## ?? Why This Project?

Creating a CEF-based desktop app with a game engine-like workflow is challenging because of:

- Window layering and input forwarding  
- Integration of C++ backend with React frontend  
- Rendering pipeline for real-time 3D content  

This project explores solutions for these problems while experimenting with modern UI and rendering techniques.
