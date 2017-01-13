#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>

/*! The 6502 CPU */
class CPU_6502 : public Cpu {
public:
	/// Create a new 6502
	explicit CPU_6502(EmuSystem * sys);
	void Init();
	void Tick();

};
