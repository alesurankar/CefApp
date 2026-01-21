#pragma once
#include "Include/cef_resource_handler.h"
#include "Include/cef_parser.h"
#include <fstream>
#include <string>
#include <filesystem>

// Step 9.1: Chromium renders the page
class NanoFileResourceHandler : public CefResourceHandler
{
public:
	bool Open(
		CefRefPtr<CefRequest> pRequest,
		bool& handleRequest,
		CefRefPtr<CefCallback> pCallback) override
	{
		handleRequest = true;

		CefURLParts urlParts;

		if (!CefParseURL(pRequest->GetURL(), urlParts))
		{
			MessageBoxA(nullptr, "Invalid URL in request.", "Request Error", MB_ICONERROR);
			return false;
		}

		try
		{
			const std::string rawPath = CefString(&urlParts.path).ToString();
			if (rawPath.empty())
			{
				MessageBoxA(nullptr, "Empty request path.", "Request Error", MB_ICONERROR);
				return false;
			}

			// Sanitize and resolve path
			const auto fullPath = "dist" / std::filesystem::path{ rawPath }.relative_path();

			// Verify file exists and is regular file
			if (!std::filesystem::exists(fullPath) || !std::filesystem::is_regular_file(fullPath))
			{
				MessageBoxA(nullptr, ("File not found:\n" + fullPath.string()).c_str(), "Request Error", MB_ICONERROR);
				return false;
			}

			// Store size and MIME type
			fileSize_ = (int64_t)std::filesystem::file_size(fullPath);
			auto ext = fullPath.extension().string();
			ext.erase(std::remove(ext.begin(), ext.end(), '.'), ext.end());

			if (!ext.empty())
			{
				fileMimeType_ = CefGetMimeType(ext);
			}

			// Open file stream
			fileStream_ = std::ifstream{ fullPath, std::ios::binary };
			if (!fileStream_.is_open())
			{
				MessageBoxA(nullptr, ("Failed to open file:\n" + fullPath.string()).c_str(), "File Error", MB_ICONERROR);
				return false;
			}
			return true;
		}
		catch (const std::exception& ex)
		{
			std::string message = "Request failed:\n";
			message += ex.what();
			MessageBoxA(nullptr, message.c_str(), "Exception Caught", MB_ICONERROR);
			return false;
		}
	}
	void GetResponseHeaders(
		CefRefPtr<CefResponse> pResponse,
		int64_t& responseLength,
		CefString& redirectUrl) override
	{
		if (!fileMimeType_.empty())
		{
			pResponse->SetMimeType(fileMimeType_);
		}
		pResponse->SetStatus(200);
		responseLength = fileSize_;
	}
	void Cancel() override {}
	bool Read(
		void* pDataOut,
		int bytesToRead,
		int& bytesRead,
		CefRefPtr<CefResourceReadCallback> pCallback) override
	{
		//if we don't have an out buffer, that's a problem
		if (!pDataOut)
		{
			bytesRead = -2;
			return false;
		}

		//attempt to read up to bytesToRead
		fileStream_.read(static_cast<char*>(pDataOut), bytesToRead);

		//gcout() is how many bytes we actually got during the last read
		bytesRead = (int)fileStream_.gcount();

		// if we got *any* bytes, return true
		// (returning false with bytesRead==0 signals EOF to CEF)
		return bytesRead > 0;
	}
private:
	std::ifstream fileStream_;
	int64_t fileSize_ = 0;
	std::string fileMimeType_;
	IMPLEMENT_REFCOUNTING(NanoFileResourceHandler);
};