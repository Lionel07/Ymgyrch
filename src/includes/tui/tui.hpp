#pragma once
#include <string>

class TextUI {
private:
	int last_cols = 0;
	int last_rows = 0;
public:
    // Status
    bool paused = false;
    bool step = false;
	bool refresh = true;
	bool refreshLog = true;
	bool refreshDis = true;
	bool refreshSys = true;
	int cols = 0;
	int rows = 0;

    // Functions
    TextUI();
	void SetColor(int fg, int bg);
	void ResetColor();
	void Clear();
	void Update();
	void Draw();
	void DrawWindow(int x, int y, int w, int h);
    void DrawWindow(int x, int y, int w, int h, std::string title);

	//
	void DrawStatus();
	void DrawLog();
	void DrawSystem();
	void DrawDisassembly();
};

extern TextUI * g_tui;