#pragma once

class TextUI {
private:
	int updates = 0;
	int cache_col = 0;
	int cache_row = 0;
	int cache_logentry_last = 0;

	bool do_cls = true;
	bool do_log = true;
	bool do_frame = true;
	bool do_debug = true;

public:
	TextUI();
	bool paused = false;
	bool stepping = false;
	void Init();
	void Update();
	void ProcessInput();
	
	void DrawLog();
	void DrawDebugger();
	void DrawFrame();
};

extern TextUI * g_tui;