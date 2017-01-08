#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>

class CCpu_6502 : public CCpu {
public:
	explicit CCpu_6502(CSystem * sys);
	void Init();
	void Tick();

};
