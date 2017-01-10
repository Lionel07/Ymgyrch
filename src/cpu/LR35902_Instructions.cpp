#include <cpu/LR35902.h>
#include <log.h>

#define LR35902CPU_DEF_LD(OPA,OPB) \
void CCpu_LR35902::op_ld_ ## OPA ## _ ## OPB (CCpu_LR35902 * cpu) {cpu->regs.OPA## = cpu->regs.OPB##;}

#define LR35902CPU_DEF_LD_N(OPA) \
void CCpu_LR35902::op_ld_ ## OPA ##_n (CCpu_LR35902 * cpu, uint8_t operand) { cpu->regs.OPA## = operand;}

#define LR35902CPU_DEF_LD_NN(OPA) \
void CCpu_LR35902::op_ld_ ## OPA ##_nn (CCpu_LR35902 * cpu, uint16_t operand) { cpu->regs.OPA## = operand;}

#define LR35902CPU_DEF_RST(num) \
void CCpu_LR35902::op_rst##num(CCpu_LR35902 * cpu) {cpu->rst(0x##num);}

#define LR35902CPU_DEF_XOR_REGN(REGA) \
void CCpu_LR35902::op_xor_ ##REGA (CCpu_LR35902 * cpu) {cpu->xor(cpu->regs.REGA##);}

#define LR35902CPU_DEF_CP_REGN(REGA) \
void CCpu_LR35902::op_cp_ ##REGA (CCpu_LR35902 * cpu) {cpu->cp(cpu->regs.REGA##);}


#define LR35902CPU_DEF_INC_N(REGA) \
void CCpu_LR35902::op_inc_ ##REGA (CCpu_LR35902 * cpu) {\
	if (sizeof(cpu->regs.REGA##) == 1) {\
		cpu->regs.REGA## = (uint8_t)cpu->inc(cpu->regs.REGA##);\
	}\
	else {\
		cpu->regs.REGA## = cpu->inc(cpu->regs.REGA##);\
	}}

#define LR35902CPU_DEF_DEC_N(REGA) \
void CCpu_LR35902::op_dec_ ##REGA (CCpu_LR35902 * cpu) { \
	cpu->regs.REGA## = cpu->dec(cpu->regs.REGA##); \
}


void CCpu_LR35902::op_reserved(CCpu_LR35902 * cpu) {
	g_log->Log(cpu->getName().c_str(), "Executed reserved instruction: 0x%X. Halting.", cpu->next_opcode);
	cpu->Stop();
}


void CCpu_LR35902::op_nop(CCpu_LR35902 * cpu) {
	cpu->regs.m += 1;
}


void CCpu_LR35902::op_jp_nn(CCpu_LR35902 * cpu, uint16_t operand) {
	cpu->regs.pc = operand;
	cpu->regs.m += 1;
}

void CCpu_LR35902::op_jr_n(CCpu_LR35902 * cpu, uint8_t operand) {
	cpu->regs.pc += (signed char)operand;
}

void CCpu_LR35902::op_jr_z_n(CCpu_LR35902 * cpu, uint8_t operand) {
	if ((cpu->regs.f & FLAGS_ZERO)) {
		cpu->regs.pc += (signed char)operand;
	}
}

void CCpu_LR35902::op_jr_c_n(CCpu_LR35902 * cpu, uint8_t operand) {
	if ((cpu->regs.f & FLAGS_CARRY)) {
		cpu->regs.pc += (signed char)operand;
	}
}

void CCpu_LR35902::op_jr_nz_n(CCpu_LR35902 * cpu, uint8_t operand) {
	if (!(cpu->regs.f & FLAGS_ZERO)) {
		cpu->regs.pc += (signed char)operand;
	}
}

void CCpu_LR35902::op_jr_nc_n(CCpu_LR35902 * cpu, uint8_t operand) {
	if (!(cpu->regs.f & FLAGS_CARRY)) {
		cpu->regs.pc += (signed char)operand;
	}
}

LR35902CPU_DEF_RST(00)
LR35902CPU_DEF_RST(08)
LR35902CPU_DEF_RST(10)
LR35902CPU_DEF_RST(18)
LR35902CPU_DEF_RST(20)
LR35902CPU_DEF_RST(28)
LR35902CPU_DEF_RST(30)
LR35902CPU_DEF_RST(38)

LR35902CPU_DEF_LD(a, b)
LR35902CPU_DEF_LD(a, c)
LR35902CPU_DEF_LD(a, d)
LR35902CPU_DEF_LD(a, e)
LR35902CPU_DEF_LD(a, h)
LR35902CPU_DEF_LD(a, l)
LR35902CPU_DEF_LD(b, a)
LR35902CPU_DEF_LD(b, c)
LR35902CPU_DEF_LD(b, d)
LR35902CPU_DEF_LD(b, e)
LR35902CPU_DEF_LD(b, h)
LR35902CPU_DEF_LD(b, l)
LR35902CPU_DEF_LD(c, a)
LR35902CPU_DEF_LD(c, b)
LR35902CPU_DEF_LD(c, d)
LR35902CPU_DEF_LD(c, e)
LR35902CPU_DEF_LD(c, h)
LR35902CPU_DEF_LD(c, l)
LR35902CPU_DEF_LD(d, a)
LR35902CPU_DEF_LD(d, b)
LR35902CPU_DEF_LD(d, c)
LR35902CPU_DEF_LD(d, e)
LR35902CPU_DEF_LD(d, h)
LR35902CPU_DEF_LD(d, l)
LR35902CPU_DEF_LD(e, a)
LR35902CPU_DEF_LD(e, b)
LR35902CPU_DEF_LD(e, c)
LR35902CPU_DEF_LD(e, d)
LR35902CPU_DEF_LD(e, h)
LR35902CPU_DEF_LD(e, l)
LR35902CPU_DEF_LD(h, a)
LR35902CPU_DEF_LD(h, b)
LR35902CPU_DEF_LD(h, c)
LR35902CPU_DEF_LD(h, d)
LR35902CPU_DEF_LD(h, e)
LR35902CPU_DEF_LD(h, l)
LR35902CPU_DEF_LD(l, a)
LR35902CPU_DEF_LD(l, b)
LR35902CPU_DEF_LD(l, c)
LR35902CPU_DEF_LD(l, d)
LR35902CPU_DEF_LD(l, e)
LR35902CPU_DEF_LD(l, h)

void CCpu_LR35902::op_ld_nn_a(CCpu_LR35902 * cpu, uint16_t operand) { cpu->sys->mem.WriteByte(operand, cpu->regs.a); }

LR35902CPU_DEF_LD_NN(bc)
LR35902CPU_DEF_LD_NN(de)
LR35902CPU_DEF_LD_NN(hl)
LR35902CPU_DEF_LD_NN(sp)

LR35902CPU_DEF_LD_N(a)
LR35902CPU_DEF_LD_N(b)
LR35902CPU_DEF_LD_N(c)
LR35902CPU_DEF_LD_N(d)
LR35902CPU_DEF_LD_N(e)
LR35902CPU_DEF_LD_N(h)
LR35902CPU_DEF_LD_N(l)

void CCpu_LR35902::op_ldi_hlp_a(CCpu_LR35902 * cpu, uint16_t operand) {
	cpu->sys->mem.WriteShort(cpu->regs.hl, cpu->regs.a);
	cpu->regs.hl++;
}

void CCpu_LR35902::op_ldd_hlp_a(CCpu_LR35902 * cpu, uint16_t operand) {
	cpu->sys->mem.WriteShort(cpu->regs.hl, cpu->regs.a);
	cpu->regs.hl--;
}

LR35902CPU_DEF_XOR_REGN(a)
LR35902CPU_DEF_XOR_REGN(b)
LR35902CPU_DEF_XOR_REGN(c)
LR35902CPU_DEF_XOR_REGN(d)
LR35902CPU_DEF_XOR_REGN(e)
LR35902CPU_DEF_XOR_REGN(h)
LR35902CPU_DEF_XOR_REGN(l)

LR35902CPU_DEF_CP_REGN(a)
LR35902CPU_DEF_CP_REGN(b)
LR35902CPU_DEF_CP_REGN(c)
LR35902CPU_DEF_CP_REGN(d)
LR35902CPU_DEF_CP_REGN(e)
LR35902CPU_DEF_CP_REGN(h)
LR35902CPU_DEF_CP_REGN(l)

void CCpu_LR35902::op_cp_n(CCpu_LR35902 * cpu, uint8_t opcode) { 
	cpu->cp(opcode);

}

//INC + DEC
LR35902CPU_DEF_INC_N(a)
LR35902CPU_DEF_INC_N(b)
LR35902CPU_DEF_INC_N(c)
LR35902CPU_DEF_INC_N(d)
LR35902CPU_DEF_INC_N(e)
LR35902CPU_DEF_INC_N(h)
LR35902CPU_DEF_INC_N(l)

LR35902CPU_DEF_DEC_N(a)
LR35902CPU_DEF_DEC_N(b)
LR35902CPU_DEF_DEC_N(c)
LR35902CPU_DEF_DEC_N(d)
LR35902CPU_DEF_DEC_N(e)
LR35902CPU_DEF_DEC_N(h)
LR35902CPU_DEF_DEC_N(l)

LR35902CPU_DEF_INC_N(bc)
LR35902CPU_DEF_INC_N(de)
LR35902CPU_DEF_INC_N(hl)
LR35902CPU_DEF_INC_N(sp)

LR35902CPU_DEF_DEC_N(bc)
LR35902CPU_DEF_DEC_N(de)
LR35902CPU_DEF_DEC_N(hl)
LR35902CPU_DEF_DEC_N(sp)

void CCpu_LR35902::op_di(CCpu_LR35902 * cpu) {
	cpu->sys->mem.WriteByte(0xFFFF, 0);
}

void CCpu_LR35902::op_ei(CCpu_LR35902 * cpu) {
	cpu->sys->mem.WriteByte(0xFFFF, 1);
}

void CCpu_LR35902::op_ldh_n_a(CCpu_LR35902 * cpu, uint8_t operand) {
	uint64_t address = cpu->sys->mem.ReadShort(0xFF00 + operand);
	cpu->sys->mem.WriteShort(address, cpu->regs.a);
}

void CCpu_LR35902::op_ldh_a_n(CCpu_LR35902 * cpu, uint8_t operand) {
	uint64_t address = cpu->sys->mem.ReadShort(0xFF00 + operand);
	cpu->regs.a = cpu->sys->mem.ReadShort(address);
}
