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
	void LoadFile(std::string path);
	/// Loads and maps an iNES rom
	void LoadINESRom(FILE * rom);
};