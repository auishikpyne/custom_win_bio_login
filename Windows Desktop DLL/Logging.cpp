// Logging.cpp
#include "pch.h" // Include the precompiled header
#include "Logging.h"
#include <fstream>
#include <sstream>
#include <windows.h>

void LogEvent(const std::wstring& message)
{
    std::wofstream logFile;
    logFile.open(L"D:\\Backup_official\\Windows Desktop DLL\\log.txt", std::ios_base::app);
    if (logFile.is_open())
    {
        SYSTEMTIME time;
        GetLocalTime(&time);
        logFile << L"[" << time.wYear << L"-" << time.wMonth << L"-" << time.wDay << L" "
            << time.wHour << L":" << time.wMinute << L":" << time.wSecond << L"] "
            << message << std::endl;
        logFile.close();
    }
}
