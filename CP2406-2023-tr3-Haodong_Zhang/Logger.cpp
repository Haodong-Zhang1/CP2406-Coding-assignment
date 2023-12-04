/*
 * Logger.cpp
 */

#include "Logger.h"

void Logger::enableLogging(bool enable)
{
    ms_loggingEnabled = enable;
}

void Logger::enableConsoleLogging(bool enable)
{
    ms_ConsoleLoggingEnabled = enable;
}

bool Logger::isLoggingEnabled()
{
    return ms_loggingEnabled;
}

