#pragma once
#include "config/MyCefConfig_client.h"
#include <cassert>

class MyCefClient
	: 
	public CefClient, 
	public CefLifeSpanHandler, 
	public CefLoadHandler
{
public:
	explicit MyCefClient(HWND hWndParent) 
		: 
		hWndParent_(hWndParent)
	{}
	CefRefPtr<CefBrowser> GetBrowser() const
	{
		return mainBrowser_;
	}
	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
	{
		return this;
	}
	CefRefPtr<CefLoadHandler> GetLoadHandler() override
	{
		return this;
	}
	bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
		CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;
	// Step 8: Browser object and HWND created
	void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override;
	// Step 10: Frame finished loading
	void OnLoadEnd(CefRefPtr<CefBrowser> pBrowser, 
		CefRefPtr<CefFrame> pFrame, int httpStatusCode) override;
	// this is the last call after Browser is destroyed
	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
private:
	HWND hWndParent_;
	CefRefPtr<CefBrowser> mainBrowser_;
	std::atomic<int> browserCount_{ 0 }; 
	IMPLEMENT_REFCOUNTING(MyCefClient);
};