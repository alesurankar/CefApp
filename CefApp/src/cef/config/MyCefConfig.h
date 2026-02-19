#pragma once

// ================= CEF PERFORMANCE CONFIGURATION =================

// --- Sandbox & Security ---
#define CEF_USE_SANDBOX 0             // Disable sandbox for simpler build (no OS-level isolation)

// --- GPU / Rendering ---
//#define CEF_USE_GPU 1                 // Keep GPU enabled for fast rendering (WebGL, CSS, video)
#define CEF_USE_MEDIA 0               // Disable unnecessary media frameworks if you don't use them
#define CEF_USE_SWIFTSHADER 0         // Disable software GPU fallback
//#define CEF_USE_V8_CONTEXT_SNAPSHOT 1 // Enable fast JavaScript initialization

// --- Browser features ---
#define CEF_ENABLE_PDF 0              // Disable PDF plugin
#define CEF_ENABLE_PRINTING 0         // Disable printing support
#define CEF_ENABLE_EXTENSIONS 0       // Disable Chrome extensions
#define CEF_ENABLE_EXTERNAL_POPUP 0   // Disable external popup windows
//#define CEF_DISABLE_COMMAND_LINE_ARGS 1 // Disable command-line argument parsing

// --- Optional performance tweaks ---
#define CEF_USE_OFF_SCREEN_RENDERING 0 // Only enable if you want headless/offscreen rendering
//#define CEF_USE_MULTIPLE_PROCESSES 1   // Keep multiple processes (renderer sandbox) for stability
#define CEF_USE_LOCAL_STORAGE 0        // Disable localStorage if not needed
#define CEF_USE_COOKIE 0               // Disable cookies if not needed

// ================= END OF CONFIGURATION =================