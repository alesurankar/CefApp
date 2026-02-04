//#include "../platform/WinWrapper.h"
//#include "MyCefApp.h"
//#include "include/wrapper/cef_closure_task.h"
//#include "include/base/cef_callback.h"
//
//
//void MyCefApp::OnContextInitialized()
//{
//    // Register custom scheme handler (used later during requests)
//    CefRegisterSchemeHandlerFactory(
//        "http", "disk", new FileSchemeHandlerFactory{}
//    );
//}
//
//void MyCefApp::OnContextCreated(CefRefPtr<CefBrowser> pBrowser,
//    CefRefPtr<CefFrame> pFrame, CefRefPtr<CefV8Context> pV8Context)
//{
//    // From JS, calling doVersion(...) goes to MyCefApp::Execute()
//    auto global = pV8Context->GetGlobal();
//    global->SetValue(
//        "function1",
//        CefV8Value::CreateFunction("function1", this),
//        V8_PROPERTY_ATTRIBUTE_NONE
//    );
//    global->SetValue(
//        "function2",
//        CefV8Value::CreateFunction("function2", this),
//        V8_PROPERTY_ATTRIBUTE_NONE
//    );
//    global->SetValue(
//        "function3",
//        CefV8Value::CreateFunction("function3", this),
//        V8_PROPERTY_ATTRIBUTE_NONE
//    );
//    global->SetValue(
//        "CloseFunc",
//        CefV8Value::CreateFunction("CloseFunc", this),
//        V8_PROPERTY_ATTRIBUTE_NONE
//    );
//    global->SetValue(
//        "MinimizeFunc",
//        CefV8Value::CreateFunction("MinimizeFunc", this),
//        V8_PROPERTY_ATTRIBUTE_NONE
//    );
//    //pFrame->ExecuteJavaScript("alert('Step8: ContextCreated!')", pFrame->GetURL(), 0);
//    pFrame->ExecuteJavaScript("console.log('Step8: ContextCreated!')", pFrame->GetURL(), 0);
//    browser_ = pBrowser;
//    currentFrame_ = pFrame;
//}
//
//bool MyCefApp::Execute(const CefString& name, CefRefPtr<CefV8Value> object,
//    const CefV8ValueList& argPtrs, CefRefPtr<CefV8Value>& pRet, CefString& exception)
//{
//    if (name == "function1") {
//        HandleFunction1(argPtrs);
//    }
//    else if (name == "function2") {
//        HandleFunction2();
//    }
//    else if (name == "function3") {
//        HandleFunction3(argPtrs);
//    }
//    else if (name == "CloseFunc") {
//        std::string action = "close";
//        HandleFunction4(action);
//    }
//    else if (name == "MinimizeFunc") {
//        std::string action = "minimize";
//        HandleFunction5(action);
//    }
//    else {
//        exception = "Unknown native function: " + name.ToString();
//        return false;
//    }
//    return true;
//}
//
//void MyCefApp::HandleFunction1(const CefV8ValueList& argPtrs)
//{
//    const auto id = nextInvocationId_++;
//    auto& invocation = invocations_[id];
//    invocation.pAccept = argPtrs[1];
//    invocation.pReject = argPtrs[2];
//    invocation.pV8Context = CefV8Context::GetCurrentContext();
//    invocation.task = std::async([this, text = argPtrs[0]->GetStringValue().ToString(), id]
//        {
//            const auto ret = MessageBoxA(nullptr, text.c_str(),
//                "hello", MB_SYSTEMMODAL | MB_ICONQUESTION | MB_YESNOCANCEL);
//            CefPostTask(TID_RENDERER, base::BindOnce(&MyCefApp::ResolveJsPromise, this,
//                id, ret == IDYES, ret == IDCANCEL ? "CAN"s : ""s
//            ));
//        });
//}
//
//void MyCefApp::HandleFunction2()
//{
//    currentFrame_->ExecuteJavaScript("alert('Function2 Executed!')", currentFrame_->GetURL(), 0);
//}
//
//void MyCefApp::HandleFunction3(const CefV8ValueList& argPtrs)
//{
//    const auto id = nextInvocationId_++;
//    auto& invocation = invocations_[id];
//
//    // Store JS callbacks for later
//    invocation.pAccept = argPtrs[1];
//    invocation.pReject = argPtrs[2];
//    invocation.pV8Context = CefV8Context::GetCurrentContext();
//
//    // Start async task (example: simulate some work)
//    invocation.task = std::async([this, text = argPtrs[0]->GetStringValue().ToString(), id]
//        {
//            // Simulate a long-running operation or user input
//            const bool success = !text.empty(); // example logic
//
//            // Resolve JS promise on renderer thread
//            CefPostTask(TID_RENDERER, base::BindOnce(&MyCefApp::ResolveJsPromise, this,
//                id, success, success ? ""s : "Text was empty"s
//            ));
//        });
//}
//
//void MyCefApp::HandleFunction4(const std::string& msg)
//{
//    if (!currentFrame_ || !browser_) return;
//    currentFrame_->ExecuteJavaScript("alert(\"Sending message: '" + msg + "' to Browser process\");", currentFrame_->GetURL(), 0);
//    CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create("TestMessage");
//    message->GetArgumentList()->SetString(0, msg);
//    currentFrame_->SendProcessMessage(PID_BROWSER, message);
//}
//
//void MyCefApp::HandleFunction5(const std::string& msg)
//{
//    if (!currentFrame_ || !browser_) return;
//    currentFrame_->ExecuteJavaScript("alert(\"Sending message: '" + msg + "' to Browser process\");", currentFrame_->GetURL(), 0);
//    CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create("TestMessage");
//    message->GetArgumentList()->SetString(0, msg);
//    currentFrame_->SendProcessMessage(PID_BROWSER, message);
//}
//
//void MyCefApp::ResolveJsPromise(uint32_t id, bool success, std::string error)
//{
//    auto& invocation = invocations_[id];    // Get the stored invocation info
//    invocation.pV8Context->Enter();         // Enter the V8 context
//    if (!error.empty()) {                   // If there’s an error 
//        // reject()
//        invocation.pReject->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateString(error) });
//    }
//    else {
//        // resolve()
//        invocation.pAccept->ExecuteFunction({}, CefV8ValueList{ CefV8Value::CreateBool(success) });
//    }
//    invocation.pV8Context->Exit();         // Leave the V8 context
//    invocations_.erase(id);                // Remove this invocation
//}