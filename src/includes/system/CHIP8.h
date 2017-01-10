#pragma once
#include <system.h>

class CSys_Chip8 : public CSystem {
public:
	CSys_Chip8();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void Reset();
	void LoadFile(std::string path);
};