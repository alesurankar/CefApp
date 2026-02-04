//#pragma once
//#include "include/cef_client.h"
//
//// Minimal Client class definition inheriting from CefClient
//class Client 
//    : 
//    public CefClient,
//    public CefLifeSpanHandler
//{
//public:
//    explicit Client(HWND hWndParent)  // lives on Win32 main thread
//        :
//        hWndParent_(hWndParent)
//    {}
//    CefRefPtr<CefBrowser> GetBrowser() const
//    {
//        return mainBrowser_;
//    }
//    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
//    {
//        return this;
//    }
//    CefRefPtr<CefLoadHandler> GetLoadHandler() override
//    {
//        return nullptr;
//    }
//    void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override;   // CEF UI Thread
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;






    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, // browser UI thread
        CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
private:
    HWND hWndParent_;              // lives on Win32 main thread
    CefRefPtr<CefBrowser> mainBrowser_;   // thread safe pointer
    IMPLEMENT_REFCOUNTING(Client);
};
