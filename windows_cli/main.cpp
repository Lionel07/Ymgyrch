#include <log.h>
#include <ymgyrch.h>
#include <stdio.h>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>
void init_debugger() {
	rlutil::cls();
	rlutil::setConsoleTitle("Ymgyrch");
	rlutil::hidecursor();
	rlutil::setColor(rlutil::WHITE);
	rlutil::setBackgroundColor(rlutil::BLACK);
	rlutil::saveDefaultColor();
	// Draw Frame
	for (int i = 1; i <= rlutil::tcols(); i++) {
		rlutil::locate(i, 1);
		rlutil::setChar(205);
		rlutil::locate(i, rlutil::trows());
		rlutil::setChar(205);
	}
	for (int i = 1; i <= rlutil::trows(); i++) {
		rlutil::locate(1, i);
		rlutil::setChar(186);
		rlutil::locate(rlutil::tcols() / 2, i);
		rlutil::setChar(186);
		rlutil::locate(rlutil::tcols(), i);
		rlutil::setChar(186);
	}

	rlutil::locate(1, 1);
	rlutil::setChar((char)201);
	rlutil::locate(rlutil::tcols(), 1);
	rlutil::setChar(187);
	rlutil::locate(rlutil::tcols(), rlutil::trows());
	rlutil::setChar(188);
	rlutil::locate(1, rlutil::trows());
	rlutil::setChar(200);

	rlutil::locate(rlutil::tcols() / 2, 1);
	rlutil::setChar(203);
	rlutil::locate(rlutil::tcols() / 2, rlutil::trows());
	rlutil::setChar(202);

	// Draw Titles
	rlutil::locate(rlutil::tcols() / 4, 1);
	printf("Log");
	rlutil::locate((rlutil::tcols() / 10) * 7, 1);
	printf("System State");
	rlutil::resetColor();
}



void draw_debugger() {
	// Draw Log
	int max_entries = rlutil::trows() - 2;
	int lastEntryIndex = g_log->buffer.size();
	int firstEntryIndex = lastEntryIndex - max_entries;
	if (firstEntryIndex < 0) firstEntryIndex = 0;
	int logPosY = 2;

	static int lastRunIndex = 0; // Only update when the log gets changed

	if (lastRunIndex != lastEntryIndex)
	{
		lastRunIndex = lastEntryIndex;
		for (int i = firstEntryIndex; i < lastEntryIndex; i++)
		{
			rlutil::locate(3, logPosY);
			printf("%-57s\n", g_log->buffer[i]);
			logPosY++;
		}
		g_log->FlushBufferToX(max_entries);
	}

	// Draw CPU INFO
	if (g_config->realTimeDebug)
	{
		int cpus = g_running_system->cpu.size();
		int cpuLogY = 2;
		for (int c = 0; c < cpus; c++)
		{
			std::vector<std::string> sysinfo = g_running_system->cpu[c]->GetRegStrings();
			for each (std::string line in sysinfo)
			{
				rlutil::locate((rlutil::tcols() / 2) + 2, cpuLogY);
				fmt::print("{0:40s}",line);
				cpuLogY++;
				
			}
		}
	}
	else
	{

	}
}

int main() {
	g_log = new Logger();
	g_log->bufferOutput = true;

	g_config = new CConfig();

	//Setup TUI
	init_debugger();

	g_log->Log("MAIN", "Initialsing");
	g_running_system = LoadSystem(GAMEBOY);
	g_log->Log("MAIN", "Loaded System: %s", g_running_system->name.c_str());
	// Start running system
	g_running_system->Init();
	g_running_system->Start();
	g_running_system->LoadFile("tetris.gb");
	draw_debugger();
	while (g_running_system->isActive) {
		g_running_system->Tick();
		draw_debugger();
		//rlutil::msleep(1000);
	}
	g_log->Log("MAIN", "Execution finished");
	draw_debugger();
	rlutil::getkey();
	return 0;
}
