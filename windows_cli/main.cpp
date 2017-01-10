#include <log.h>
#include <ymgyrch.h>
#include <stdio.h>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>

int tui_update_counter = 0;
int tui_last_col = 0;
int tui_last_row = 0;
int tui_last_logentry = 0;

void tui_init() {
	rlutil::cls();
	rlutil::setConsoleTitle("Ymgyrch");
	rlutil::hidecursor();
	rlutil::setColor(rlutil::WHITE);
	rlutil::setBackgroundColor(rlutil::BLACK);
	rlutil::saveDefaultColor();
	g_config->displayMode = g_config->TUI;
	g_config->tui_cols = rlutil::tcols();
	g_config->tui_rows = rlutil::trows();
}

void tui_drawFrame() {
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

void tui_drawDebugger() {
	if (g_running_system == nullptr) { return; }
	if (g_config == nullptr) { return; }
	if (!g_config->realTimeDebug) {
		rlutil::locate((rlutil::tcols() / 2) + (rlutil::tcols() / 8), 4);
		fmt::print("Real Time Debugger Disabled");
		return;
	}
	
	int cpus = g_running_system->cpu.size();
	int cpuLogY = 2;
	for (int c = 0; c < cpus; c++)
	{
		std::vector<std::string> sysinfo = g_running_system->cpu[c]->GetRegStrings();
		for each (std::string line in sysinfo)
		{
			rlutil::locate((rlutil::tcols() / 2) + 2, cpuLogY);
			fmt::print("{0}",line);
			cpuLogY++;
		}
	}
}

void tui_drawLog() {
	int max_entries = rlutil::trows() - 2;
	int lastEntryIndex = g_log->buffer.size();
	int firstEntryIndex = lastEntryIndex - max_entries;
	if (firstEntryIndex < 0) firstEntryIndex = 0;
	int logPosY = 2;
	for (int i = firstEntryIndex; i < lastEntryIndex; i++)
	{
		rlutil::locate(3, logPosY);
		fmt::print("{0}", g_log->buffer[i]);
		logPosY++;
	}
	g_log->FlushBufferToX(max_entries);
}


void tui_update() {
	bool updateLog = false;
	bool updateFrame = false;
	bool updateDebugger = false;
	bool clearScreen = false;

	if (rlutil::trows() != tui_last_row || rlutil::tcols() != tui_last_col) // Force everything to update on screen resize
	{
		clearScreen = true;
		updateFrame = true;
		updateLog = true;
		updateDebugger = true;
		tui_last_row = rlutil::trows();
		tui_last_col = rlutil::tcols();
		g_config->tui_cols = rlutil::tcols();
		g_config->tui_rows = rlutil::trows();
	}

	if (tui_last_logentry != g_log->buffer.size()) // Update if the log is changed
	{
		tui_last_logentry = g_log->buffer.size();
		updateLog = true;
	}

	if (g_config->realTimeDebug == true)
	{
		updateDebugger = true;
	}

	if (clearScreen) { rlutil::cls(); }
	if (updateFrame) { tui_drawFrame(); }
	if (updateLog) { tui_drawLog(); }
	if (updateDebugger) { tui_drawDebugger(); }
	tui_update_counter++;
}


int main() {
	g_log = new Logger();
	g_log->bufferOutput = true;
	g_config = new CConfig();
	tui_init();

	g_running_system = LoadSystem(CHIP8);
	g_log->Log("MAIN", "Loaded System: {}", g_running_system->name);

	// Start running system
	g_running_system->Init();
	g_running_system->Start();
	g_running_system->LoadFile("PONG");

	while (g_running_system->isActive) {
		g_running_system->Tick();
		tui_update();
	}
	char ret = rlutil::getkey();
	return 0;
}
