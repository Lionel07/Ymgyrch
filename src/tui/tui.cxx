#include <tui/tui.hpp>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>
#include <logging.hpp>
#include <ymgyrch/cpu.hpp>
#include <ymgyrch/core.hpp>
#include <ymgyrch/state.hpp>
#include <vector>

static size_t cachedLogSize = 0;
static int numUpdates = 0;
TextUI * g_tui;

TextUI::TextUI() {
	rlutil::cls();
	rlutil::setConsoleTitle("Ymgyrch");
	rlutil::hidecursor();
	rlutil::setColor(rlutil::WHITE);
	rlutil::setBackgroundColor(rlutil::BLACK);
	rlutil::saveDefaultColor();
	cols = rlutil::tcols();
	rows = rlutil::trows();
	last_cols = cols;
	last_rows = rows;
}

void TextUI::Update() {
	cols = rlutil::tcols();
	rows = rlutil::trows();
	rlutil::hidecursor();
	if (cols != last_cols || rows != last_rows) {
		last_cols = cols;
		last_rows = rows;
		refresh = true;
	}
	
	if (g_log->buffer.size() > cachedLogSize) { refreshLog = true; }
}

void TextUI::Draw() {
	numUpdates++;
	if (numUpdates > 60) {
		refresh = true;
		numUpdates = 0;
	}
	if (refresh) {
		Clear();
	}
	if (refreshLog || refresh) {
		DrawLog();
	}
	if (refreshDis || refresh) {
		DrawDisassembly();
	}
	if (refreshSys || refresh) {
		DrawSystem();
	}
	if (refresh) {
		DrawStatus();
	}
	
	refresh = false;
	refreshLog = false;
	refreshDis = true;
	refreshSys = true;
}
void TextUI::DrawSystem()
{
	ResetColor();
	DrawWindow(0, rows - 8, cols - 1, 6, "Status");

	std::vector<Ymgyrch::cpu_info_t> info = g_core->current->cpus[0]->GetStatus();
	
	int y = 0;
	int x = 0;
	for each (Ymgyrch::cpu_info_t line in info)
	{
		rlutil::locate(3 + (x * 24), rows - 6 + y);
		fmt::print("{0:8s}| {1:16s}", line.name, line.data);
		y++;
		if (y == 5) { y = 0; x++; }
	}
}

void TextUI::DrawDisassembly()
{
	int mid = (int)floor((float)cols / (float)3) * 2;
	int x = mid - 1;
	int y = 0;

	ResetColor();
	DrawWindow(mid - 1, 0, (mid / 2), rows - 9, "Dissassembly");
	State::disassembly.lines = rows - 10;

	std::vector<Ymgyrch::cpu_instruction_t> info = g_core->current->cpus[0]->GetDissassembly();

	int i = 0;
	for each (Ymgyrch::cpu_instruction_t line in info)
	{
		rlutil::locate(x + 3, y + 2 + i); i++;
		if (line.current) {
			fmt::print("> 0x{0:04X}| {1:16s}", line.address, line.dissassembly);
		}
		else if (line.endofreliable) {
			fmt::print("! 0x{0:04X}| {1:16s}", line.address, line.dissassembly);
		}
		else {
			fmt::print("  0x{0:04X}| {1:16s}", line.address, line.dissassembly);
		}
	}
}
void TextUI::Clear() {
	ResetColor();
	rlutil::cls();
}

void TextUI::SetColor(int fg, int bg) {
	rlutil::setColor(fg);
	rlutil::setBackgroundColor(bg);
}

void TextUI::ResetColor() {
	rlutil::resetColor();
}

void TextUI::DrawStatus() {
	SetColor(rlutil::WHITE, rlutil::LIGHTBLUE);
	for (int dx = 1; dx < cols; dx++) {
		rlutil::locate(dx, rows);
		putchar(' ');
	}
	//TODO: Get last character working
	rlutil::locate(2, rows);
	printf("Status: READY");
}

void TextUI::DrawLog()
{
	ResetColor();
	int mid = (int)floor((float)cols / (float)3)  - 1;
	int max_entries = rows - 10;
	int logPosY = 2;

	DrawWindow(0, 0, mid * 2, rows - 9, "Log");	

	int lastEntryIndex = g_log->buffer.size();
	int firstEntryIndex = lastEntryIndex - max_entries;
	if (firstEntryIndex < 0) firstEntryIndex = 0;
		
	for (int i = firstEntryIndex; i < lastEntryIndex; i++)
	{
		rlutil::locate(3, logPosY);

		std::string fmt_str = "{0: <40s}";
		if (cols > 100) {
			fmt_str = "{0: <60s}";
		}

		fmt::print(fmt_str, g_log->buffer[i]);
		logPosY++;
	}
	g_log->FlushBufferToX(max_entries);
	cachedLogSize = g_log->buffer.size();
}



void TextUI::DrawWindow(int x, int y, int w, int h) {
	char top_left     = (char)201; //╔
	char top_right    = (char)187; //╗
	char horizontal   = (char)205; //═
	char vertical     = (char)186; //║
	char bottom_left  = (char)200; //╚
	char bottom_right = (char)188; //╝
	// Console coordinates are 1 based, but display coordniates are 0 based
	x += 1;
	y += 1;

	rlutil::locate(x, y); putchar(top_left);
	rlutil::locate(x + w, y); putchar(top_right);
	rlutil::locate(x, y + h); putchar(bottom_left);
	rlutil::locate(x + w, y + h); putchar(bottom_right);

	// Clear space
	/*
	for (int dx = x + 1; dx < x + w; dx++) {
		for (int dy = y + 1; dy < y + h; dy++) {
			rlutil::locate(dx, dy);
			putchar(' ');
		}
	}*/

	// Draw borders
	for (int dx = x + 1; dx < x + w; dx++) {
		rlutil::locate(dx, y);
		putchar(horizontal);
		rlutil::locate(dx, h + y);
		putchar(horizontal);
	}
	for (int dy = y + 1; dy < y + h; dy++) {
		rlutil::locate(x, dy);
		putchar(vertical);
		rlutil::locate(x + w, dy);
		putchar(vertical);
	}
}

void TextUI::DrawWindow(int x, int y, int w, int h, std::string title) {
	DrawWindow(x, y, w, h);
	size_t start = (w / 2) - (title.length() / 2) + x + 1;
	rlutil::locate(start, y + 1);
	printf("%s", title.c_str());
}
