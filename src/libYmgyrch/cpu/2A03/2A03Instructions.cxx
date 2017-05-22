#include <ymgyrch/system.hpp>
#include <ymgyrch/cpu.hpp>
#include <ymgyrch/cpu/2A03.hpp>
#include <ymgyrch/state.hpp>
#include <logging.hpp>
#include <functional>

#define OPCODE(x) void Ymgyrch::Cpus::CPU2A03::Opcode_##x()
#define PEEK(x) sys->memController->ReadByte(x)
#define FLAG_CARRY 1
#define FLAG_ZERO 2
#define FLAG_INT 4
#define FLAG_BRK 16
#define FLAG_OVERFLOW 64
#define FLAG_SIGN 128

#define SET_FLAG(f) registers.p |= ##f
#define CLR_FLAG(f) registers.p &= ##f
#define TST_FLAG(f) !!(registers.p & ##f)

#define VAL_ZP sys->memController->ReadByte(sys->memController->ReadByte(registers.pc + 1))
#define VAL_DX (char)(PEEK(PEEK(PEEK(registers.pc + 1) + registers.x) % 256) + (PEEK((PEEK(registers.pc + 1) + registers.x + 1) % 256) * 256));
#define VAL_IM sys->memController->ReadByte(registers.pc + 1)
#define CYCLE(x) registers.cycles += x; registers.cyclesDelta += x;

#define CMP()  \
	a = b - a; \
	if (a == 0) { SET_FLAG(FLAG_ZERO); } else { CLR_FLAG(FLAG_ZERO); } \
	if (a < 0) { SET_FLAG(FLAG_CARRY); } else { CLR_FLAG(FLAG_CARRY); } \

OPCODE(ukn) {
	g_log->Error("2A03", "Invalid opcode 0x{0:X}", sys->memController->ReadByte(registers.pc));
	CYCLE(100000000); registers.pc++; //sys->Stop();
}
// System
OPCODE(brk) { sys->Stop(); CYCLE(100000000); }
OPCODE(nop) { registers.pc++; CYCLE(2); }
// Inc
OPCODE(inx) { registers.pc++; registers.x++; CYCLE(2); }
OPCODE(iny) { registers.pc++; registers.y++; CYCLE(2); }
// Transfer
OPCODE(txa) { registers.a = registers.x; CYCLE(2); registers.pc++; }
OPCODE(txs) { registers.s = registers.x; CYCLE(2); registers.pc++; }
OPCODE(tax) { registers.x = registers.a; CYCLE(2); registers.pc++; }
OPCODE(tsx) { registers.x = registers.s; CYCLE(2); registers.pc++; }
OPCODE(tya) { registers.a = registers.y; CYCLE(2); registers.pc++; }
OPCODE(tay) { registers.y = registers.a; CYCLE(2); registers.pc++;}
// Load
OPCODE(lda_im) { registers.a = VAL_IM; CYCLE(2); registers.pc += 2; }
OPCODE(ldx_im) { registers.x = VAL_IM; CYCLE(2); registers.pc += 2; }
OPCODE(ldy_im) { registers.y = VAL_IM; CYCLE(2); registers.pc += 2; }
// Jumps
OPCODE(jmp) { registers.pc = sys->memController->ReadWord(registers.pc + 1); CYCLE(3); }
OPCODE(jsr) {
	uint16_t absolute = sys->memController->ReadByte(registers.pc + 1) + registers.pc;
	registers.s -= 2;  sys->memController->WriteWord(registers.s, absolute);
	registers.pc = absolute; CYCLE(6);
	g_log->Log("2A03", "Jump to 0x{0:X}", registers.pc);
}

OPCODE(cmp_im) {
	signed short a = registers.a; signed short b = VAL_IM; CMP();
	CYCLE(2); registers.pc += 2;
}

OPCODE(cmp_zp) {
	signed short a = registers.a; signed short b = VAL_ZP; CMP();
	CYCLE(2); registers.pc += 2;
}

OPCODE(cmp_zpx) {
	signed short b = VAL_DX; signed short a = registers.a; CMP();
	CYCLE(6); registers.pc += 2;
}

OPCODE(cpx_im) {
	signed short a = registers.x; signed short b = VAL_IM; CMP();
	CYCLE(2); registers.pc += 2;
}

OPCODE(cpx_zp) {
	signed short b = VAL_ZP; signed short a = registers.x; CMP();
	CYCLE(6); registers.pc += 2;
}

OPCODE(cpy_im) {
	signed short a = registers.y; signed short b = VAL_IM; CMP();
	CYCLE(2); registers.pc += 2;
}

OPCODE(cpy_zp) {
	signed short b = VAL_ZP; signed short a = registers.y; CMP();
	CYCLE(2); registers.pc += 2;
}
