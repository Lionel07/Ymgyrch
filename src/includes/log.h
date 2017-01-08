#pragma once
#include <string>
#include <cstdarg>
#include <vector>
#include <deque>
enum LogLevel
{
	LOG_DEBUG = 0,
	LOG_LOG = 1,
	LOG_WARN = 2,
	LOG_ERROR = 3
};

class Logger
{
	void DoLog(const char *sys, const char *fmt, va_list a, va_list b);

public:
	Logger();
	~Logger();
	bool bufferOutput = false;
	std::deque<char *> buffer;
	void Log(const char * component, const char * fmt, ...);
	void FlushBufferToX(int x);

};

extern Logger * g_log;