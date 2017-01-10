#include <stdio.h>
#include <cstdarg>
#include <vector>
#include <log.h>
#include <libfmt/fmt/format.h>
#include <libfmt/fmt/printf.h>
Logger * g_log;

void Logger::DoLog(std::string sys, std::string message)
{
	fmt::MemoryWriter final_message;
	final_message.write(fmt::format("{0:5s}: {1:s}", sys, message));

	if (bufferOutput)
	{
		buffer.push_back(final_message.str());
	}
	else
	{
		//fmt::print("{0:s}\n", final_message);
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
	int num = buffer.size() - x;
	if (num < 1)
	{
		return;
	}
	for (int i = 0; i < num; i++)
	{
		std::string entry = buffer.front();
		buffer.pop_front();
	}
}
