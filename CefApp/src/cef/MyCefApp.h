#pragma once
#include "include/cef_app.h"
#include "../resources/FileSchemeHandlerFactory.h"
#include <future>
#include <unordered_map>

using namespace std::string_literals;

class MyCefApp
    :
    public CefApp,
    public CefBrowserProcessHandler,
    public CefRenderProcessHandler,
    public CefV8Handler
{
    struct Invocation_
    {
        CefRefPtr<CefV8Value> pAccept;
        CefRefPtr<CefV8Value> pReject;
        CefRefPtr<CefV8Context> pV8Context;
        std::future<void> task;
    };
public:
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
    {
        return this;
    }
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override
    {
        return this;
    }
    // Step 3: Global CEF context initialized (browser-independent)
    void OnContextInitialized() override;
    //Step 7: JS context created (V8 ready, DOM may not be loaded yet)
    void OnContextCreated(CefRefPtr<CefBrowser> pBrowser, 
        CefRefPtr<CefFrame> pFrame, CefRefPtr<CefV8Context> pV8Context) override;
    // Step X: JS <-> C++ bridge
    bool Execute(const CefString& name, CefRefPtr<CefV8Value> object, 
        const CefV8ValueList& argPtrs, CefRefPtr<CefV8Value>& pRet, CefString& exception) override;
private:
    void HandleFunction1(const CefV8ValueList& argPtrs);
    void HandleFunction2();
    void HandleFunction3(const CefV8ValueList& argPtrs);
    void ResolveJsPromise(uint32_t id, bool success, std::string error);
private:
    uint32_t nextInvocationId_ = 0;
    std::unordered_map<uint32_t, Invocation_> invocations_;
    CefRefPtr<CefFrame> currentFrame_; 
    IMPLEMENT_REFCOUNTING(MyCefApp);
};