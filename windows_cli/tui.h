#pragma once

/*! The Text UI */
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
	/// Constructor
	TextUI();
	/// Is the core paused
	bool paused = false;
	/// True only if we're stepping one instruction
	bool stepping = false;
	/// Setup the TUI
	void Init();
	/// Runs every frame
	void Update();
	/// Processes keyboard input every frame
	void ProcessInput();
	
	/// Draw the log
	void DrawLog();
	/// Draw the Debugger
	void DrawDebugger();
	/// Draw the border of the window
	void DrawFrame();
};

extern TextUI * g_tui;