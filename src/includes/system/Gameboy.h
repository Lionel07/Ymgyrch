#pragma once
#include <system.h>

class CSys_Gameboy : public CSystem {
public:
	CSys_Gameboy();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void Reset();
	void LoadFile(std::string path);
};