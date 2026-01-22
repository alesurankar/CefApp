#pragma once
#include "include/cef_app.h"
#include "Include/wrapper/cef_closure_task.h"
#include "Include/base/cef_callback.h"
#include "NanoFileSchemeHandlerFactory.h"
#include <future>
#include <unordered_map>

using namespace std::string_literals;

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
    void OnContextInitialized() override
    {
        // Register custom scheme handler (used later during requests)
        CefRegisterSchemeHandlerFactory(
            "http", "disk", new NanoFileSchemeHandlerFactory{}
        );
    }
    //Step 7: JS context created (V8 ready, DOM may not be loaded yet)
    void OnContextCreated(
        CefRefPtr<CefBrowser> pBrowser, 
        CefRefPtr<CefFrame> pFrame, 
        CefRefPtr<CefV8Context> pV8Context
    ) override
    {
        // From JS, calling doVersion(...) goes to NanoCefApp::Execute()
        auto global = pV8Context->GetGlobal();
        global->SetValue(
            "doVersion", 
            CefV8Value::CreateFunction("doVersion", this), 
            V8_PROPERTY_ATTRIBUTE_NONE
        );
        global->SetValue(
            "function2",
            CefV8Value::CreateFunction("function2", this),
            V8_PROPERTY_ATTRIBUTE_NONE
        );
        //pFrame->ExecuteJavaScript("alert('Step8: ContextCreated!')", pFrame->GetURL(), 0);
        pFrame->ExecuteJavaScript("console.log('Step8: ContextCreated!')", pFrame->GetURL(), 0);
    }
    // Step X: JS <-> C++ bridge
    bool Execute(
        const CefString& name,
        CefRefPtr<CefV8Value> object,
        const CefV8ValueList& argPtrs,
        CefRefPtr<CefV8Value>& pRet,
        CefString& exception
    ) override
    {
        if (name == "doVersion") {
            HandleDoVersion(argPtrs);
        }
        else if (name == "function2") {
            // this is a placeholder for next function
        }
        else {
            exception = "Unknown native function: " + name.ToString();
            return false;
        }
        return true;
    }

private:
    void HandleDoVersion(const CefV8ValueList&  argPtrs)
    {
        const auto id = nextInvocationId_++;
        auto& invocation = invocations_[id];
        invocation.pAccept = argPtrs[1];
        invocation.pReject = argPtrs[2];
        invocation.pV8Context = CefV8Context::GetCurrentContext();
        invocation.task = std::async([this, text = argPtrs[0]->GetStringValue().ToString(), id]
            {
                const auto ret = MessageBoxA(nullptr, text.c_str(),
                    "henlo", MB_SYSTEMMODAL | MB_ICONQUESTION | MB_YESNOCANCEL);
                CefPostTask(TID_RENDERER, base::BindOnce(&NanoCefApp::ResolveJsPromise, this,
                    id, ret == IDYES, ret == IDCANCEL ? "CAN"s : ""s
                ));
            });
    }
    void ResolveJsPromise(uint32_t id, bool success, std::string error)
    {
        auto& invocation = invocations_[id];    // Get the stored invocation info
        invocation.pV8Context->Enter();         // Enter the V8 context
        if (!error.empty())                 // If there’s an error
        {
            // reject()
            invocation.pReject->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateString(error) });
        }
        else
        {
            // resolve()
            invocation.pAccept->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateBool(success) });
        }
        invocation.pV8Context->Exit();         // Leave the V8 context
        invocations_.erase(id);                // Remove this invocation
    }

    uint32_t nextInvocationId_ = 0;
    std::unordered_map<uint32_t, Invocation_> invocations_;
private:
    IMPLEMENT_REFCOUNTING(NanoCefApp);
};