#include <stdio.h>
#include <cstdarg>
#include <vector>
#include <log.h>
#include <libfmt/fmt/format.h>
#include <libfmt/fmt/printf.h>
#include <ymgyrch.h>
Logger * g_log;

void Logger::DoLog(std::string sys, std::string message)
{
	fmt::MemoryWriter final_message;
	final_message.write(fmt::format("{0:8s}: {1:s}", sys, message));

	if (!Ymgyrch::config->log.logToStdio)
	{
		buffer.push_back(final_message.str());
	}
	else
	{
		fmt::print("{0:s}\n", final_message.str());
	}
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
	int lower_limit = g_log->buffer.size() - x;

	if (lower_limit < 0) {
		lower_limit = 0;
	}

	for (size_t i = 0; i < lower_limit; i++) {
		buffer.pop_front();
	}
}