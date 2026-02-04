//#pragma once
//#include "include/cef_client.h"
//#include <cassert>
//
//class MyCefClient
//	: 
//	public CefClient, 
//	public CefLifeSpanHandler, 
//	public CefLoadHandler
//{
//public:
//	explicit MyCefClient(HWND hWndParent) 
//		: 
//		hWndParent_(hWndParent)
//	{}
//	CefRefPtr<CefBrowser> GetBrowser() const
//	{
//		return mainBrowser_;
//	}
//	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
//	{
//		return this;
//	}
//	CefRefPtr<CefLoadHandler> GetLoadHandler() override
//	{
//		return this;
//	}
//	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
//		CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
//	// Step 8: Browser object and HWND created
//	// At this point:
//	// - The browser object exists
//	// - The child window (HWND) exists
//	// - Renderer process has started
//	// - Page may not have loaded yet
//	void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override;
//	// Step 10: Page finished loading
//	// At this point:
//	// - Main frame and all content (HTML/CSS/JS) is fully loaded
//	// - Safe to access DOM elements or execute JS that depends on the page
//	void OnLoadEnd(CefRefPtr<CefBrowser> pBrowser, 
//		CefRefPtr<CefFrame> pFrame, int httpStatusCode) override;
//	// this is the last call after Browser is destroyed
//	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
//private:
//	HWND hWndParent_;
//	CefRefPtr<CefBrowser> mainBrowser_;
//	IMPLEMENT_REFCOUNTING(MyCefClient);
//};