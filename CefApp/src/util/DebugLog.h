
////////////////////////////////////////
// Initialize once and use everywhere //
////////////////////////////////////////

#pragma once
#include <fstream>
#include <mutex>
#include <string>

class Logger {
private:
    static std::ofstream ofs_;
    static std::mutex mtx_;
public:
    static void Init(const std::string& filename);
    static void Log(const std::string& msg);
    static void Close();
};