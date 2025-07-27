#pragma once
#include "include/cef_app.h"
#include "NanoFileSchemeHandlerFactory.h"
#include <future>
#include <unordered_map>

class NanoCefApp
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
    void OnContextInitialized() override
    {
        CefRegisterSchemeHandlerFactory("http", "disk", new NanoFileSchemeHandlerFactory{});
    }
    void OnContextCreated(CefRefPtr<CefBrowser> pBrowser, CefRefPtr<CefFrame> pFrame, CefRefPtr<CefV8Context> pV8Context)
    {
        pV8Context->GetGlobal()->SetValue("doVersion", CefV8Value::CreateFunction("doVersion", this), V8_PROPERTY_ATTRIBUTE_NONE);
    }
    bool Execute(const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& argPtrs,
        CefRefPtr<CefV8Value>& pRet,
        CefString& exception) override
    {
        const auto id = nextInvocationId_++;
        auto& invocation = invocations_[id];
        invocation.pAccept = argPtrs[1];
        invocation.pReject = argPtrs[2];
        invocation.task = std::async([this, text = argPtrs[0]->GetStringValue().ToString(), id]
            {
                auto ret = MessageBoxA(nullptr, text.c_str(),
                    "henlo", MB_SYSTEMMODAL | MB_ICONQUESTION | MB_YESNOCANCEL);
                if (ret == IDCANCEL)
                {
                    invocations_[id].pReject->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateString("CAN") });
                }
                else
                {
                    invocations_[id].pAccept->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateBool(ret == IDYES) });
                }
            });
        return true;
    }

private:
    uint32_t nextInvocationId_ = 0;
    std::unordered_map<uint32_t, Invocation_> invocations_;

    IMPLEMENT_REFCOUNTING(NanoCefApp);
};