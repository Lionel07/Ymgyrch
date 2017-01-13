#pragma once
#include <system.h>

/*! A Chip8 (not SCHIP) */

class System_Chip8 : public EmuSystem {
public:
	System_Chip8();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void Reset();
	void LoadFile(std::string path);
};