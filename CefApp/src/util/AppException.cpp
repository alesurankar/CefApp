#include "AppException.h"
#include <sstream>


// AppException
std::string AppException::TranslateErrorCode(HRESULT hr) noexcept
{
    char* pMsgBuf = nullptr;
    // windows will allocate memory for err string and make our pointer point to it
    const DWORD nMsgLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
    );
    // 0 string length returned indicates a failure
    if (nMsgLen == 0)
    {
        return "Unidentified error code";
    }
    // copy error string from windows-allocated buffer to std::string
    std::string errorString = pMsgBuf;
    // remove trailing \r or \n
    while (!errorString.empty() && (errorString.back() == '\r' || errorString.back() == '\n')) {
        errorString.pop_back();
    }
    LocalFree(pMsgBuf);
    return errorString;
}


// HrException
HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
    :
    AppException(line, file),
    hr(hr)
{
    // join all info messages with newlines into single string
    for (const auto& m : infoMsgs)
    {
        info += m;
        info.push_back('\n');
    }
    // remove final newline if exists
    if (!info.empty())
    {
        info.pop_back();
    }
}

const char* HrException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << "\n"
        << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
        << std::dec << " (" << static_cast<unsigned long>(GetErrorCode()) << ")" << "\n"
        << "[Description] " << GetErrorDescription() << "\n";
    if (!info.empty())
    {
        oss << "\n[Error Info]\n" << GetErrorInfo() << "\n" << "\n";
    }
    oss << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* HrException::GetType() const noexcept
{
    return "App Exception [HrException]";
}

HRESULT HrException::GetErrorCode() const noexcept
{
    return hr;
}

std::string HrException::GetErrorDescription() const noexcept
{
    return TranslateErrorCode(hr);
}

std::string HrException::GetErrorInfo() const noexcept
{
    return info;
}


// InfoException
InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
    :
    AppException(line, file)
{
    // join all info messages with newlines into single string
    for (const auto& m : infoMsgs)
    {
        info += m;
        info.push_back('\n');
    }
    // remove final newline if exists
    if (!info.empty())
    {
        info.pop_back();
    }
}

const char* InfoException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << "\n"
        << "\n[Error Info]\n" << GetErrorInfo() << "\n" << "\n";
    oss << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* InfoException::GetType() const noexcept
{
    return "App Exception [InfoException]";
}

std::string InfoException::GetErrorInfo() const noexcept
{
    return info;
}


// NoGfxException
const char* NoGfxException::GetType() const noexcept
{
    return "App Exception [NoGfxException]";
}


// DeviceRemovedException
DeviceRemovedException::DeviceRemovedException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
    :
    HrException(line, file, hr, infoMsgs)
{
    reason = TranslateErrorCode(hr);
}

const char* DeviceRemovedException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << "\n"
        << "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
        << std::dec << " (" << static_cast<unsigned long>(GetErrorCode()) << ")\n"
        << "[Reason] " << reason << "\n";

    // include extra info messages from HrException
    if (!GetErrorInfo().empty())
        oss << "\n[Error Info]\n" << GetErrorInfo() << "\n";

    oss << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* DeviceRemovedException::GetType() const noexcept
{
    return "App Exception [DeviceRemovedException]";
}
