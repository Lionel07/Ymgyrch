#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>

/*! The Chip8's CPU */
class CPU_Chip8 : public Cpu {
private:
	typedef struct registers {
		uint8_t v[16];
		uint16_t I;
		uint16_t pc;
		uint16_t sp;
		uint8_t timer_delay;
		uint8_t timer_sound;
	} regs_t;

	regs_t regs;

public:
	/// Creates a new Chip8 CPU
	explicit CPU_Chip8(EmuSystem * sys);
	void Init();
	/// Logs the current instruction to the debug log
	void DissassembleAndLog(uint16_t opcode);
	void Tick();
	virtual std::vector<std::string> GetRegStrings();
};
