#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>

class CCpu_Chip8 : public CCpu {
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
	explicit CCpu_Chip8(CSystem * sys);
	void Init();
	void DissassembleAndLog(uint16_t opcode);
	void Tick();
	virtual std::vector<std::string> GetRegStrings();
};
