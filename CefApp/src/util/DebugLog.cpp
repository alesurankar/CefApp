// DebugLog.cpp
#include "DebugLog.h"

std::ofstream Logger::ofs_;
std::mutex Logger::mtx_;

void Logger::Init(const std::string& filename) 
{
    if (ofs_.is_open()) {
        ofs_.close();
    }
    ofs_.open(filename, std::ios::out | std::ios::trunc);
}

void Logger::Log(const std::string& msg) 
{
    std::lock_guard<std::mutex> lock(mtx_);
    ofs_ << msg << '\n';
    ofs_.flush();
}

void Logger::Close() 
{
    ofs_.close();
}