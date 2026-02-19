#pragma once

// ======= CEF CONFIGURATION =======

// Disable sandbox (simplifies build, reduces overhead if you don't need security isolation)
#define CEF_USE_SANDBOX 0

// Disable PDF plugin
#define CEF_ENABLE_PDF 0

// Disable printing support
#define CEF_ENABLE_PRINTING 0

// Disable external popups
#define CEF_ENABLE_EXTERNAL_POPUP 0

// Disable extensions (Chrome extensions are not needed for lightweight CEF)
#define CEF_ENABLE_EXTENSIONS 0

// Disable media features if not needed (optional)
#define CEF_USE_MEDIA 0

// Disable command-line arguments parsing if you don't need it
#define CEF_DISABLE_COMMAND_LINE_ARGS 1

// Add more macros here as needed
