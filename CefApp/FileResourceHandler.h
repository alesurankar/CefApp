#pragma once
#include "Include/cef_resource_handler.h"
#include "Include/cef_parser.h"
#include <fstream>
#include <string>
#include <filesystem>

class FileResourceHandler 
	: 
	public CefResourceHandler
{
public:
	// Step 9.1 Network + resource handling
	bool Open(CefRefPtr<CefRequest> pRequest, bool& handleRequest, 
		CefRefPtr<CefCallback> pCallback) override;
	void GetResponseHeaders(CefRefPtr<CefResponse> pResponse, 
		int64_t& responseLength, CefString& redirectUrl) override;
	void Cancel() override {}
	// Step 9.2 Network + resource handling
	bool Read(void* pDataOut, int bytesToRead, int& bytesRead, 
		CefRefPtr<CefResourceReadCallback> pCallback) override;
private:
	std::ifstream fileStream_;
	int64_t fileSize_ = 0;
	std::string fileMimeType_;
	IMPLEMENT_REFCOUNTING(FileResourceHandler);
};