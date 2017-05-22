#pragma once
#include <ymgyrch/cpu.hpp>
#include <string>


namespace Ymgyrch {
namespace Cpus {
class CPU2A03 : public Ymgyrch::Cpu {
public:
	struct registers {
		uint8_t a;
		uint8_t x;
		uint8_t y;
		uint8_t p;
		uint8_t s;
		uint16_t pc;
		uint64_t cycles = 0;
		uint64_t cyclesDelta = 0;
	} registers;
	virtual void Init(Ymgyrch::System * sys);
	virtual void Update();
	virtual void Reset();
	virtual std::vector<cpu_instruction_t> GetDissassembly();
	virtual std::vector<cpu_info_t> GetStatus();

	typedef void (CPU2A03::*InstructionImpl)();
	typedef struct opcode {
		std::string dissassembly;
		Cpus::CPU2A03::InstructionImpl op;
		int operandSize = 0;
	} opcode_t;

	static opcode_t opcodes[256];
	#define DEF_OPCODE(x) void Opcode_##x()

	DEF_OPCODE(ukn);
	DEF_OPCODE(brk);
	DEF_OPCODE(nop);

	// INC
	DEF_OPCODE(inx);
	DEF_OPCODE(iny);
	// Branch
	DEF_OPCODE(jmp);
	DEF_OPCODE(jsr);

	DEF_OPCODE(cmp_im);
	DEF_OPCODE(cmp_zp);
	DEF_OPCODE(cmp_zpx);

	DEF_OPCODE(cpx_im);
	DEF_OPCODE(cpx_ab);
	DEF_OPCODE(cpx_zp);

	DEF_OPCODE(cpy_im);
	DEF_OPCODE(cpy_ab);
	DEF_OPCODE(cpy_zp);

	DEF_OPCODE(txa);
	DEF_OPCODE(txs);
	DEF_OPCODE(tax);
	DEF_OPCODE(tsx);
	DEF_OPCODE(tya);
	DEF_OPCODE(tay);

	DEF_OPCODE(lda_im);
	DEF_OPCODE(ldx_im);
	DEF_OPCODE(ldy_im);

};
};
};

#undef DEF_OPCODE