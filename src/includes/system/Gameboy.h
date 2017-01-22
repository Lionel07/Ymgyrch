#pragma once
#include <system.h>


/*! A Gameboy */
class System_Gameboy : public Ymgyrch::System {
public:
	System_Gameboy();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void SubTick() {};
	void Reset();
	void LoadFile(std::string path);
};