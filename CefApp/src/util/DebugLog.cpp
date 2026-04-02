// DebugLog.cpp
#include "DebugLog.h"

std::ofstream Logger::ofs_;
std::mutex Logger::mtx_;

void Logger::Init(const std::string& filename) {
    ofs_.open(filename, std::ios::out | std::ios::app);
}

void Logger::Log(const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx_);
    ofs_ << msg << std::endl;
}

void Logger::Close() {
    ofs_.close();
}