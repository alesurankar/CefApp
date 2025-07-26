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

private:
	HWND hWndParent_;
	CefRefPtr<CefBrowser> pBrowser_;

	IMPLEMENT_REFCOUNTING(NanoCefClient);
};