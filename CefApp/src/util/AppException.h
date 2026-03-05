#pragma once
#include "MyException.h"
#include <string>
#include <sstream>


class AppException : public MyException
{
public:
	AppException(int line, const char* file, const std::string& note) noexcept
		:
		MyException(line, file), note(note)
	{
	}
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