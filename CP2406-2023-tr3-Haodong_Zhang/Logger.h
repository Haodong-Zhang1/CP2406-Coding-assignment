/*
 * Logger.h
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger
{
public:
    static void enableLogging(bool enable);

    //enable console logging
    static void enableConsoleLogging(bool enable);

    static bool isLoggingEnabled();

    template<typename ... Args>
    static void log(const Args &... args);
private:
    static inline const string ms_debugFilename
    { "debugfile.out" };
    static inline bool ms_loggingEnabled
    { false };
    static inline bool ms_ConsoleLoggingEnabled
    { false };
};

template<typename ... Args>
void Logger::log(const Args &... args)
{
    if (!ms_loggingEnabled)
    {
        return;
    }

    ofstream logfile
    { ms_debugFilename, ios_base::app };

    if (logfile.fail())
    {
        cerr << "Unable to open debug file!" << endl;
        return;
    }

    // Use a C++17 unary right fold, see Chapter 26.
    ((logfile << args),...);
    logfile << endl;

    if (ms_ConsoleLoggingEnabled)
    {
        cout << "Log: ";
        ((cout << args),...);
        cout << endl;
    }
}
#endif

