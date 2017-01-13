#pragma once
#include <system.h>


/*! A Gameboy */
class System_Gameboy : public EmuSystem {
public:
	System_Gameboy();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void Reset();
	void LoadFile(std::string path);
};