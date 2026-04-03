
////////////////////////////////////////
// Initialize once and use everywhere //
////////////////////////////////////////

#pragma once
#include <fstream>
#include <mutex>
#include <string>

#ifdef NDEBUG
#define DBG_LOG(msg) do {} while(0)
#else
#define DBG_LOG(msg) do { Logger::Log(msg); } while(0)
#endif

class Logger {
public:
    static void Init(const std::string& filename);
    static void Log(const std::string& msg);
    static void Close();
private:
    static std::ofstream ofs_;
    static std::mutex mtx_;
};