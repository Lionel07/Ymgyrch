#pragma once
#include <system.h>

/*! A Nintendo Entertainment System */
class System_Nes : public EmuSystem {
public:
	System_Nes();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void Reset();
};