#pragma once
#include "include/cef_client.h"
#include <cassert>

class NanoCefClient : public CefClient, public CefLifeSpanHandler
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

	// Step 7: Browser HWND created. At this point, the browser is visible
	void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override
	{
		assert(pBrowser);
		pBrowser_ = pBrowser;
		HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
		if (hWndBrowser)
		{
			RECT rect{};
			GetClientRect(hWndParent_, &rect);

			SetWindowPos(hWndBrowser, NULL, rect.left, rect.top,
				rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
		}
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