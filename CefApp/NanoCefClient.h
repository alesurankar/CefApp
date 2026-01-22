#pragma once
#include "include/cef_client.h"
#include <cassert>

class NanoCefClient 
	: 
	public CefClient, 
	public CefLifeSpanHandler, 
	public CefLoadHandler
{
public:
	explicit NanoCefClient(HWND hWndParent) : hWndParent_(hWndParent)
	{
	}

	CefRefPtr<CefBrowser> GetBrowser() const
	{
		return pBrowser_;
	}

	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
	{
		return this;
	}

	CefRefPtr<CefLoadHandler> GetLoadHandler() override
	{
		return this;
	}

	// Step 8: Browser object and HWND created
	// At this point:
	// - The browser object exists
	// - The child window (HWND) exists
	// - Renderer process has started
	// - Page may not have loaded yet
	void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override
	{
		assert(pBrowser);
		pBrowser_ = pBrowser;
		HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
		if (hWndBrowser)
		{
			RECT rect{};
			GetClientRect(hWndParent_, &rect);
			SetWindowPos(hWndBrowser, NULL, 0, 0,
				rect.right - rect.left,
				rect.bottom - rect.top, SWP_NOZORDER);

			// Safe to run JS now, but page may not be fully loaded
			//pBrowser->GetMainFrame()->ExecuteJavaScript(
			//	"alert('Step7: Browser initialized!');",
			//	pBrowser->GetMainFrame()->GetURL(), 0
			//);
			pBrowser->GetMainFrame()->ExecuteJavaScript(
				"console.log('Step7: Browser initialized!');",
				pBrowser->GetMainFrame()->GetURL(), 0
			);
		}
	}

	// Step 10: Page finished loading
	// At this point:
	// - Main frame and all content (HTML/CSS/JS) is fully loaded
	// - Safe to access DOM elements or execute JS that depends on the page
	void OnLoadEnd(
		CefRefPtr<CefBrowser> pBrowser,
		CefRefPtr<CefFrame> pFrame,
		int httpStatusCode
	) override
	{
		pFrame->ExecuteJavaScript("alert('Step9: Page loaded!')", pFrame->GetURL(), 0);
		pFrame->ExecuteJavaScript("console.log('Step9: Page loaded!')", pFrame->GetURL(), 0);
	}

	// this is the last call after Browser is destroyed
	void OnBeforeClose(CefRefPtr<CefBrowser> browser) override
	{
		pBrowser_ = nullptr; 
		PostMessage(hWndParent_, WM_CLOSE, 0, 0);
	}

private:
	HWND hWndParent_;
	CefRefPtr<CefBrowser> pBrowser_;

	IMPLEMENT_REFCOUNTING(NanoCefClient);
};