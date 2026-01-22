#pragma once
#include "include/cef_scheme.h"
#include "FileResourceHandler.h"

// Step 3 Global CEF phase (no browser yet)
class FileSchemeHandlerFactory 
    : 
    public CefSchemeHandlerFactory
{
public:
    // Step 9 Network + resource handling
    CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        const CefString& scheme_name,
        CefRefPtr<CefRequest> request) override
    {
        return new FileResourceHandler{};
    }
private:
    IMPLEMENT_REFCOUNTING(FileSchemeHandlerFactory);
};