#pragma once
#include <string>
#include <cstdarg>
#include <vector>
#include <deque>
#include <libfmt/fmt/ostream.h>
#include <libfmt/fmt/format.h>

/// All log levels
enum LogLevel
{
	LOG_DEBUG = 0,
	LOG_LOG = 1,
	LOG_WARN = 2,
	LOG_ERROR = 3,
	LOG_PANIC = 4
};

/*! The emulators log */
class Logger
{
private:
	void DoLog(std::string sys, std::string message);
public:
	/// Buffered output
	std::deque<std::string> buffer;

	/// Log a debug message.
	void Debug(std::string component, std::string format, fmt::ArgList args);
	/// Log a debug message.
	void Log(std::string component, std::string format, fmt::ArgList args);
	/// Log a debug message.
	void Warn(std::string component, std::string format, fmt::ArgList args);
	/// Log an error
	void Error(std::string component, std::string format, fmt::ArgList args);
	/// Log an unignorable message.
	void Panic(std::string component, std::string format, fmt::ArgList args);
	FMT_VARIADIC(void, Debug, std::string, std::string)
	FMT_VARIADIC(void, Log, std::string, std::string)
	FMT_VARIADIC(void, Warn, std::string, std::string)
	FMT_VARIADIC(void, Error, std::string, std::string)
	FMT_VARIADIC(void, Panic, std::string, std::string)

	/// Deletes old entries in the buffer so there are x left
	void FlushBufferToX(int x);

};

extern Logger * g_log;
