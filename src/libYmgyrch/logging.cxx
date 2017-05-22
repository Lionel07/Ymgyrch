#include <stdio.h>
#include <cstdarg>
#include <vector>
#include <logging.hpp>
#include <libfmt/fmt/format.h>
#include <libfmt/fmt/printf.h>
Logger * g_log;

void Logger::DoLog(std::string sys, std::string message)
{
	buffer.push_back(fmt::format("{0:8s}{2:c} {1:s}", sys, message, (char)186));
}

void Logger::Debug(std::string component, std::string format, fmt::ArgList args)
{
	DoLog(component, fmt::format(format, args));
}
void Logger::Log(std::string component, std::string format, fmt::ArgList args)
{
	DoLog(component, fmt::format(format, args));
}
void Logger::Warn(std::string component, std::string format, fmt::ArgList args)
{
	DoLog(component, fmt::format(format, args));
}
void Logger::Error(std::string component, std::string format, fmt::ArgList args)
{
	DoLog(component, fmt::format(format, args));
}
void Logger::Panic(std::string component, std::string format, fmt::ArgList args)
{
	DoLog(component, fmt::format(format, args));
}

void Logger::FlushBufferToX(int x)
{
	long lower_limit = g_log->buffer.size() - x;

	if (lower_limit < 0) {lower_limit = 0;}

	for (size_t i = 0; i < lower_limit; i++) {
		buffer.pop_front();
	}
}
