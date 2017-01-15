#include <rlutil/rlutil.h>
#include <ymgyrch.h>
#include <log.h>
#include "tui.h"

TextUI * g_tui;

TextUI::TextUI() {
	

}

void TextUI::Init()
{
	rlutil::cls();
	rlutil::setConsoleTitle("Ymgyrch");
	rlutil::hidecursor();
	rlutil::setColor(rlutil::WHITE);
	rlutil::setBackgroundColor(rlutil::BLACK);
	rlutil::saveDefaultColor();
	g_config->emulator.displayMode = g_config->TUI;
	g_config->tui.cols = rlutil::tcols();
	g_config->tui.rows = rlutil::trows();

	cache_col = g_config->tui.cols;
	cache_row = g_config->tui.rows;
}

void TextUI::Update() {
	// What should we draw?
	if (cache_logentry_last != g_log->buffer.size()) // Update if the log is changed
	{
		cache_logentry_last = g_log->buffer.size();
		do_log = true;
	}
	if (g_config->tui.showDebugger == true) { // If we're debugging

		if (paused && stepping)
		{
			do_debug = true;
		}

		if (!paused)
		{
			do_debug = true;
		}

		if ((updates % 1000) == 0) {
			do_debug = true; 
		}

	} 

	if ((updates % 100) == 0) { // On screen size change
		int c_rows = rlutil::trows();
		int c_cols = rlutil::tcols();

		if (c_rows != cache_row || c_cols != cache_col) {
			do_cls = true;
			do_frame = true;
			do_log = true;
			do_debug = true;

			cache_row = c_rows;
			cache_col = c_cols;
			g_config->tui.cols = cache_col;
			g_config->tui.rows = cache_row;

		}
	}

	// Do drawing
	if (do_cls) { rlutil::cls(); do_cls = false; }
	if (do_frame) { DrawFrame(); do_frame = false; }
	if (do_log) { DrawLog(); do_log = false; }
	if (do_debug) { DrawDebugger(); do_debug = false; }
	updates++;

}

void TextUI::ProcessInput()
{
	char input = rlutil::nb_getch();
	if (input != 0)
	{
		if (input == '`') // Swap real time debugging on and off 
		{
			g_config->tui.showDebugger = !g_config->tui.showDebugger;
			do_cls = true;
			do_frame = true;
			do_log = true;
			do_debug = true;

			int c_rows = rlutil::trows();
			int c_cols = rlutil::tcols();

			cache_row = c_rows;
			cache_col = c_cols;
			g_config->tui.cols = cache_col;
			g_config->tui.rows = cache_row;

		}
		if (input == 'p') // Pause
		{
			paused = !paused;
		}
		if (input == ' ') // Step
		{
			stepping = true;
		}
		if (input == 'r') // Reset
		{
			g_running_system->Reset();
			do_cls = true;
			do_frame = true;
			do_log = true;
			do_debug = true;
		}
	}
}

void TextUI::DrawLog()
{
	int max_entries = rlutil::trows() - 2;
	int lastEntryIndex = g_log->buffer.size();
	int firstEntryIndex = lastEntryIndex - max_entries;
		if (firstEntryIndex < 0) firstEntryIndex = 0;
		int logPosY = 2;
	for (int i = firstEntryIndex; i < lastEntryIndex; i++)
	{
		rlutil::locate(3, logPosY);
		fmt::print("{0:35s}", g_log->buffer[i]);
		logPosY++;
	}
	g_log->FlushBufferToX(max_entries);
}

void TextUI::DrawDebugger()
{
	if (g_running_system == nullptr) { return; }
	if (g_config == nullptr) { return; }
	if (!g_config->tui.showDebugger) {
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
			fmt::print("{0}", line);
			cpuLogY++;
		}
	}
}

void TextUI::DrawFrame()
{
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
	rlutil::locate(((rlutil::tcols() / 4) * 3) - 5, 1);
	printf("System State");
}
