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
		bool i = true;
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
		uint8_t operandSize = 0;
	} opcode_t;

	static opcode_t opcodes[256];
	#define DEF_OPCODE(x) void Opcode_##x()

	DEF_OPCODE(ukn);
	DEF_OPCODE(brk);
	DEF_OPCODE(nop);
	DEF_OPCODE(sei);
	DEF_OPCODE(cli);
	DEF_OPCODE(sed);
	DEF_OPCODE(cld);
	// INC
	DEF_OPCODE(inx);
	DEF_OPCODE(iny);
	DEF_OPCODE(dex);
	DEF_OPCODE(dey);
	// Branch
	DEF_OPCODE(jmp);
	DEF_OPCODE(jsr);
	DEF_OPCODE(bne);
	DEF_OPCODE(beq);

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
	DEF_OPCODE(lda_zp);
	DEF_OPCODE(ldx_zp);
	DEF_OPCODE(ldy_zp);
	DEF_OPCODE(lda_zpx);
	DEF_OPCODE(ldx_zpy);
	DEF_OPCODE(ldy_zpx);
	DEF_OPCODE(lda_ab);
	DEF_OPCODE(ldx_ab);
	DEF_OPCODE(ldy_ab);
	DEF_OPCODE(lda_abx);
	DEF_OPCODE(ldy_abx);
	DEF_OPCODE(lda_aby);
	DEF_OPCODE(ldx_aby);

	DEF_OPCODE(sta_ab);
	DEF_OPCODE(stx_ab);
	DEF_OPCODE(sty_ab);
	DEF_OPCODE(sta_zp);
	DEF_OPCODE(stx_zp);
	DEF_OPCODE(sty_zp);
	DEF_OPCODE(sta_zpx);
	DEF_OPCODE(stx_zpy);
	DEF_OPCODE(sty_zpx);
	DEF_OPCODE(sta_zpy);
	DEF_OPCODE(sta_abx);
	DEF_OPCODE(sta_aby);

	DEF_OPCODE(sta_zpxi);
	DEF_OPCODE(sta_zpyi);


	DEF_OPCODE(ora_im);
	DEF_OPCODE(ora_zp);
	DEF_OPCODE(ora_zpx);
	DEF_OPCODE(ora_zpxi);
	DEF_OPCODE(ora_zpyi);
	DEF_OPCODE(ora_ab);
	DEF_OPCODE(ora_abx);
	DEF_OPCODE(ora_aby);
};
};
};

#undef DEF_OPCODE