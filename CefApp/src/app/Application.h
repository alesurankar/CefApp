#pragma once
#include "../platform/MyWin.h"
#include "../util/MyException.h"
#include <string>
#include <sstream>


class AppException : public MyException
{
public:
	AppException(int line, const char* file, const std::string& note) noexcept
		: 
		MyException(line, file), note(note) 
	{}
	const char* what() const noexcept override
	{
		std::ostringstream oss;
		oss << GetType() << "\n"
			<< note << "\n"
			<< GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}
private:
	std::string note;
};

class Application 
{
public:
	Application() = default;
	~Application() = default;
	int Run(HINSTANCE hInstance);
	void EnableRealTimeLoop(bool enable) { useRealTimeLoop_ = enable; }
private:
	bool Initialize(HINSTANCE hInstance);
	int RunMessageLoop();
	int RunRealTimeLoop();
	int RunBlockingLoop();
	void Shutdown();
private:
	HINSTANCE hInstance_ = nullptr;
	HWND mainWindow_ = nullptr;
	bool running_ = false;
	bool useRealTimeLoop_ = false;
};