#pragma once
#include <string>
#include <cstdarg>
#include <vector>
#include <deque>
#include <libfmt/fmt/ostream.h>
#include <libfmt/fmt/format.h>
enum LogLevel
{
	LOG_DEBUG = 0,
	LOG_LOG = 1,
	LOG_WARN = 2,
	LOG_ERROR = 3
};

class Logger
{
private:
	void DoLog(std::string sys, std::string message);
public:
	bool bufferOutput = false;
	std::deque<std::string> buffer;

	
	void Debug(std::string component, std::string format, fmt::ArgList args);
	void Log(std::string component, std::string format, fmt::ArgList args);
	void Warn(std::string component, std::string format, fmt::ArgList args);
	void Error(std::string component, std::string format, fmt::ArgList args);
	void Panic(std::string component, std::string format, fmt::ArgList args);
	FMT_VARIADIC(void, Debug, std::string, std::string)
	FMT_VARIADIC(void, Log, std::string, std::string)
	FMT_VARIADIC(void, Warn, std::string, std::string)
	FMT_VARIADIC(void, Error, std::string, std::string)
	FMT_VARIADIC(void, Panic, std::string, std::string)
	void FlushBufferToX(int x);

};

extern Logger * g_log;