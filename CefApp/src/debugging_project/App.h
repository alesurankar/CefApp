//#pragma once
//#include "include/cef_app.h"
//
//// Implement all pure virtual methods from CefApp and its base classes.
//class App 
//    :
//    public CefApp 
//{
//public:
//    App() = default;
//
//    // CefApp
//    void OnBeforeCommandLineProcessing(const CefString& process_type, 
//        CefRefPtr<CefCommandLine> command_line) override {}
//    void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override {}
//    CefRefPtr<CefResourceBundleHandler> GetResourceBundleHandler() override { return nullptr; }
//    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return nullptr; }
//    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return nullptr; }
//
//private:
//    IMPLEMENT_REFCOUNTING(App);
//};