#include <ymgyrch/system.hpp>
#include <ymgyrch/cpu.hpp>
#include <ymgyrch/cpu/2A03.hpp>
#include <ymgyrch/state.hpp>
#include <logging.hpp>
#include <functional>

#define OPCODE(x) void Ymgyrch::Cpus::CPU2A03::Opcode_##x()
#define PEEK(x) sys->memController->ReadByte(x)
#define PEEK2(x) sys->memController->ReadShort(x)
#define POKE(x, addr)  sys->memController->WriteByte(addr,x)
#define POKE2(x, addr) sys->memController->WriteShort(addr, x)

#define FLAG_CARRY 1
#define FLAG_ZERO 2
#define FLAG_INT 4
#define FLAG_BRK 16
#define FLAG_OVERFLOW 64
#define FLAG_SIGN 128

#define SET_FLAG(f) registers.p |= ##f
#define CLR_FLAG(f) registers.p &= ##f
#define TST_FLAG(f) !!(registers.p & ##f)

#define VAL_IM registers.pc + 1
#define VAL_AB sys->memController->ReadShort(registers.pc + 1)
#define VAL_ZP sys->memController->ReadByte(registers.pc + 1)
#define VAL_ZPX (PEEK(PEEK(registers.pc + 1) + registers.x) % 256) + (PEEK((PEEK(registers.pc + 1) + registers.x + 1) % 256) * 256)
#define VAL_ZPY (PEEK(PEEK(registers.pc + 1) + registers.y) % 256) + (PEEK((PEEK(registers.pc + 1) + registers.y + 1) % 256) * 256)
#define VAL_ABX PEEK2(registers.pc + 1) + registers.x
#define VAL_ABY PEEK2(registers.pc + 1) + registers.y
#define VAL_ZPXI sys->memController->ReadShort(VAL_IM + registers.x)
#define VAL_ZPYI sys->memController->ReadShort(VAL_IM + registers.y)

#define CYCLE(x) registers.cycles += x; registers.cyclesDelta += x;

#define OP_CMP(name,reg, val) void Ymgyrch::Cpus::CPU2A03::Opcode_##name() { \
	signed short a = registers.##reg; signed short b = val; \
	a = b - a; \
	if (a == 0) { SET_FLAG(FLAG_ZERO); } else { CLR_FLAG(FLAG_ZERO); } \
	if (a < 0) { SET_FLAG(FLAG_CARRY); } else { CLR_FLAG(FLAG_CARRY); } \
	CYCLE(2); registers.pc += 2; \
}

//TODO: Set flags
#define OP_OR(name, val)  void Ymgyrch::Cpus::CPU2A03::Opcode_##name() { \
	registers.a = val | registers.a; \
	CYCLE(2); registers.pc += 2; \
}

#define OP_BRANCH(name, flag, eq) void Ymgyrch::Cpus::CPU2A03::Opcode_##name() { \
	uint16_t absolute = VAL_IM + registers.pc; \
	if (TST_FLAG(flag) == eq) { registers.pc = absolute; } \
	else { registers.pc += 2; } \
	CYCLE(6); \
}


OPCODE(ukn) {
	//g_log->Error("2A03", "Invalid opcode 0x{0:X}", sys->memController->ReadByte(registers.pc));
	CYCLE(100000000);
	sys->Stop();
}
// System
OPCODE(brk) { sys->Stop(); CYCLE(100000000); }
OPCODE(nop) { registers.pc++; CYCLE(2); }
OPCODE(sei) { registers.pc++; registers.i = false; CYCLE(2); }
OPCODE(cli) { registers.pc++; registers.i = true;  CYCLE(2); }
OPCODE(cld) { registers.pc++; CYCLE(2); }
OPCODE(sed) { registers.pc++; CYCLE(2); }
// Inc
OPCODE(inx) { registers.pc++; registers.x++; CYCLE(2); }
OPCODE(iny) { registers.pc++; registers.y++; CYCLE(2); }
OPCODE(dex) { registers.pc++; registers.x--; CYCLE(2); }
OPCODE(dey) { registers.pc++; registers.y--; CYCLE(2); }
// Transfer
OPCODE(txa) { registers.a = registers.x; CYCLE(2); registers.pc++; }
OPCODE(txs) { registers.s = registers.x; CYCLE(2); registers.pc++; }
OPCODE(tax) { registers.x = registers.a; CYCLE(2); registers.pc++; }
OPCODE(tsx) { registers.x = registers.s; CYCLE(2); registers.pc++; }
OPCODE(tya) { registers.a = registers.y; CYCLE(2); registers.pc++; }
OPCODE(tay) { registers.y = registers.a; CYCLE(2); registers.pc++;}
// Load
OPCODE(lda_im)  { registers.a = PEEK(VAL_IM); CYCLE(2); registers.pc += 2; }
OPCODE(ldx_im)  { registers.x = PEEK(VAL_IM); CYCLE(2); registers.pc += 2; }
OPCODE(ldy_im)  { registers.y = PEEK(VAL_IM); CYCLE(2); registers.pc += 2; }
OPCODE(lda_zp)  { registers.a = PEEK(VAL_ZP); CYCLE(2); registers.pc += 2; }
OPCODE(ldx_zp)  { registers.x = PEEK(VAL_ZP); CYCLE(2); registers.pc += 2; }
OPCODE(ldy_zp)  { registers.y = PEEK(VAL_ZP); CYCLE(2); registers.pc += 2; }
OPCODE(lda_zpx) { registers.a = PEEK(VAL_ZPX); CYCLE(2); registers.pc += 2;}
OPCODE(ldx_zpy) { registers.x = PEEK(VAL_ZPY); CYCLE(2); registers.pc += 2;}
OPCODE(ldy_zpx) { registers.y = PEEK(VAL_ZPX); CYCLE(2); registers.pc += 2;}
OPCODE(lda_ab)  { registers.a = PEEK(VAL_AB); CYCLE(2); registers.pc += 3; }
OPCODE(ldx_ab)  { registers.x = PEEK(VAL_AB); CYCLE(2); registers.pc += 3; }
OPCODE(ldy_ab)  { registers.y = PEEK(VAL_AB); CYCLE(2); registers.pc += 3; }
OPCODE(lda_abx) { registers.a = PEEK(VAL_ABX); CYCLE(2); registers.pc += 3;}
OPCODE(ldy_abx) { registers.y = PEEK(VAL_ABX); CYCLE(2); registers.pc += 3;}
OPCODE(lda_aby) { registers.a = PEEK(VAL_ABY); CYCLE(2); registers.pc += 3;}
OPCODE(ldx_aby) { registers.x = PEEK(VAL_ABY); CYCLE(2); registers.pc += 3;}
// Stores
OPCODE(sta_ab) { POKE(registers.a, VAL_AB); CYCLE(2); registers.pc += 3; }
OPCODE(stx_ab) { POKE(registers.x, VAL_AB); CYCLE(2); registers.pc += 3; }
OPCODE(sty_ab) { POKE(registers.y, VAL_AB); CYCLE(2); registers.pc += 3; }
OPCODE(sta_zp) { POKE(registers.a, VAL_ZP); CYCLE(2); registers.pc += 2; }
OPCODE(stx_zp) { POKE(registers.x, VAL_ZP); CYCLE(2); registers.pc += 2; }
OPCODE(sty_zp) { POKE(registers.y, VAL_ZP); CYCLE(2); registers.pc += 2; }
OPCODE(sta_zpx) { POKE(registers.a, VAL_ZPX); CYCLE(2); registers.pc += 2; }
OPCODE(stx_zpy) { POKE(registers.x, VAL_ZPY); CYCLE(2); registers.pc += 2; }
OPCODE(sty_zpx) { POKE(registers.y, VAL_ZPX); CYCLE(2); registers.pc += 2; }
OPCODE(sta_zpy) { POKE(registers.a, VAL_ZPY); CYCLE(2); registers.pc += 2; }
OPCODE(sta_zpxi) { POKE(registers.a, VAL_ZPXI); CYCLE(2); registers.pc += 2; }
OPCODE(sta_zpyi) { POKE(registers.a, VAL_ZPYI); CYCLE(2); registers.pc += 2; }
OPCODE(sta_abx) { POKE(registers.a, VAL_ABX); CYCLE(2); registers.pc += 3; }
OPCODE(sta_aby) { POKE(registers.a, VAL_ABY); CYCLE(2); registers.pc += 3; }

// Comparisons
OP_CMP(cmp_im, a, PEEK(VAL_IM));
OP_CMP(cmp_zp, a, PEEK(VAL_ZP));
OP_CMP(cmp_zpx, a, PEEK(VAL_ZPX));
OP_CMP(cpx_im, x, PEEK(VAL_IM));
OP_CMP(cpx_zp, x, PEEK(VAL_ZP));
OP_CMP(cpy_im, y, PEEK(VAL_IM));
OP_CMP(cpy_zp, y, PEEK(VAL_ZP));
// Or
OP_OR(ora_im, PEEK(VAL_IM));
OP_OR(ora_zp, PEEK(VAL_ZP));
OP_OR(ora_zpx, PEEK(VAL_ZPX));
OP_OR(ora_zpxi, PEEK(VAL_ZPXI));
OP_OR(ora_zpyi, PEEK(VAL_ZPYI));
OP_OR(ora_ab, PEEK(VAL_AB));
OP_OR(ora_abx, PEEK(VAL_ABX));
OP_OR(ora_aby, PEEK(VAL_ABY));
// Jumps
OP_BRANCH(bne, FLAG_ZERO, 0);
OP_BRANCH(beq, FLAG_ZERO, 1);
OPCODE(jmp) {
	g_log->Debug("2A03", "Jump from 0x{0:04x} => 0x{1:04x}",
		registers.pc, sys->memController->ReadShort(registers.pc + 1));
	registers.pc = sys->memController->ReadShort(registers.pc + 1); CYCLE(3); }
OPCODE(jsr) {
	uint16_t absolute = VAL_IM + registers.pc;
	registers.s -= 2;  sys->memController->WriteShort(registers.s, absolute);
	registers.pc = absolute; CYCLE(6);
	g_log->Log("2A03", "Jump to 0x{0:X}", registers.pc);
}
