#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>

template <typename T>
inline T const& Max(T const& a, T const& b) {
	return a < b ? b : a;
}

/*! The 6502 CPU */
class CPU_6502 : public Cpu {
private:
	typedef struct registers {
		uint8_t a;
		uint8_t x;
		uint8_t y;

		uint8_t  p;
		uint8_t  sp;
		uint16_t pc;
	} regs_t;

	regs_t regs;
public:

	enum Model
	{
		MODEL_GENERIC = 0,
		MODEL_2A03 = 1
	};

	Model model = MODEL_GENERIC;
	/// Create a new 6502
	explicit CPU_6502(EmuSystem * sys);
	explicit CPU_6502(EmuSystem * sys, Model model);
	void Init();
	void Tick();

};
