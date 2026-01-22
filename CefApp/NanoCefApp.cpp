#include "MyWin.h"
#include "NanoCefApp.h"
#include "Include/wrapper/cef_closure_task.h"
#include "Include/base/cef_callback.h"


void NanoCefApp::OnContextInitialized()
{
    // Register custom scheme handler (used later during requests)
    CefRegisterSchemeHandlerFactory(
        "http", "disk", new FileSchemeHandlerFactory{}
    );
}

void NanoCefApp::OnContextCreated(CefRefPtr<CefBrowser> pBrowser, 
    CefRefPtr<CefFrame> pFrame, CefRefPtr<CefV8Context> pV8Context)
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

bool NanoCefApp::Execute(const CefString& name, CefRefPtr<CefV8Value> object, 
    const CefV8ValueList& argPtrs, CefRefPtr<CefV8Value>& pRet, CefString& exception)
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

void NanoCefApp::HandleDoVersion(const CefV8ValueList& argPtrs)
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

void NanoCefApp::ResolveJsPromise(uint32_t id, bool success, std::string error)
{
    auto& invocation = invocations_[id];    // Get the stored invocation info
    invocation.pV8Context->Enter();         // Enter the V8 context
    if (!error.empty()) {                   // If there’s an error 
        // reject()
        invocation.pReject->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateString(error) });
    }
    else {
        // resolve()
        invocation.pAccept->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateBool(success) });
    }
    invocation.pV8Context->Exit();         // Leave the V8 context
    invocations_.erase(id);                // Remove this invocation
}