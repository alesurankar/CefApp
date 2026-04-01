#pragma once
#include "MyException.h"
#include <platform/MyWin.h>
#include <vector>
#include <string>


class AppException : public MyException
{
protected:
	using MyException::MyException;
public:
	static std::string TranslateErrorCode(HRESULT hr) noexcept;
};

class HrException : public AppException
{
public:
	HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
	const char* what() const noexcept override;
	const char* GetType() const noexcept override;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorDescription() const noexcept;
	std::string GetErrorInfo() const noexcept;
private:
	HRESULT hr;
	std::string info;
};

class InfoException : public AppException
{
public:
	InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
	const char* what() const noexcept override;
	const char* GetType() const noexcept override;
	std::string GetErrorInfo() const noexcept;
private:
	std::string info;
};

class NoGfxException : public AppException
{
public:
	using AppException::AppException;
	const char* GetType() const noexcept override;
};

class DeviceRemovedException : public HrException
{
	using HrException::HrException;
public:
	DeviceRemovedException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept;
	const char* what() const noexcept override;
	const char* GetType() const noexcept override;
private:
	std::string reason;
};