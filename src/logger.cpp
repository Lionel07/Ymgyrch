#include "includes\log.h"
#include <stdio.h>
#include <cstdarg>
#include <vector>
Logger * g_log;

void Logger::DoLog(const char * sys, const char * fmt, va_list a, va_list b)
{
	std::vector<char> buf(1 + std::vsnprintf(NULL, 0, fmt, b));
	std::vsnprintf(buf.data(), buf.size(), fmt, a);
	if (bufferOutput)
	{
		char * buffed = new char[25 + buf.size()];
		std::sprintf(buffed,"%-5s: %s", sys, buf.data());
		buffer.push_back(buffed);
	}
	else
	{
		std::printf("%16s : %s\n", sys, buf.data());
	}
	
}

Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::Log(const char * component, const char * fmt, ...)
{
	va_list a, b;
	va_start(a, fmt);
	va_copy(b, a);
	DoLog(component, fmt, a, b);
	va_end(a);
	va_end(b);
}

void Logger::FlushBufferToX(int x)
{
	int num = buffer.size() - x;
	if (num < 1)
	{
		return;
	}
	for (int i = 0; i < num; i++)
	{
		char * entry = buffer.front();
		buffer.pop_front();
		delete entry;
	}
}

