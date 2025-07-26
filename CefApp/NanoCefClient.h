#pragma once
#include "include/cef_client.h"
#include <cassert>

class NanoCefClient : public CefClient, public CefLifeSpanHandler
{
public:
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
	}
private:
	CefRefPtr<CefBrowser> pBrowser_;

	IMPLEMENT_REFCOUNTING(NanoCefClient);
};