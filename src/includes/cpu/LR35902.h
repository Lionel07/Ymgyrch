#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>
#include <stdint.h>

#define OP_0(name) static void op_##name (CCpu_LR35902 * cpu);
#define OP_1(name) static void op_##name (CCpu_LR35902 * cpu,  uint8_t operand);
#define OP_2(name) static void op_##name (CCpu_LR35902 * cpu,  uint16_t operand);

#define FLAGS_ZERO (1 << 7)
#define FLAGS_NEGATIVE (1 << 6)
#define FLAGS_HALFCARRY (1 << 5)
#define FLAGS_CARRY (1 << 4)

#define FLAGS_ISZERO (regs.f & FLAGS_ZERO)
#define FLAGS_ISNEGATIVE (regs.f & FLAGS_NEGATIVE)
#define FLAGS_ISCARRY (regs.f & FLAGS_CARRY)
#define FLAGS_ISHALFCARRY (regs.f & FLAGS_HALFCARRY)

#define FLAGS_ISSET(x) (regs.f & (x))
#define FLAGS_SET(x) (regs.f |= (x))
#define FLAGS_CLEAR(x) (regs.f &= ~(x))

class CCpu_LR35902 : public CCpu {
private:

	typedef struct registers {
		struct {
			union {
				struct {
					uint8_t f;
					uint8_t a;
				};
				uint16_t af;
			};
		};

		struct {
			union {
				struct {
					uint8_t c;
					uint8_t b;
				};
				uint16_t bc;
			};
		};

		struct {
			union {
				struct {
					uint8_t e;
					uint8_t d;
				};
				uint16_t de;
			};
		};

		struct {
			union {
				struct {
					uint8_t l;
					uint8_t h;
				};
				uint16_t hl;
			};
		};

		uint16_t sp;
		uint16_t pc;
		uint16_t m;
		uint16_t t;
	} regs_t;

	typedef struct cpuinstruction {
		std::string name;
		unsigned char length;
		void *run;
	} cpu_instruction_t;

	regs_t regs;
	uint8_t next_opcode;
	cpu_instruction_t instructions[256];
	
	bool flag_ime = false;
	bool firstTimeSetup = false;
public:

	explicit CCpu_LR35902(CSystem * sys);
	void TeachInstructions();
	void Init();
	void Tick();
	void PrintRegs();
	std::vector<std::string> GetRegStrings();
	char * DisassembleInstruction(uint16_t pc);
	void FetchNext();

	// Operations
	void xor(uint8_t num);
	void rst(uint8_t num);
	void cp(uint16_t value);
	uint16_t inc(uint16_t num);
	uint16_t dec(uint16_t num);
	

	// Instructions declared here
	OP_0(nop)
	OP_0(ei)
	OP_0(di)

	// Jumps
	OP_2(jp_nn)
	OP_1(jr_n)
	OP_1(jr_z_n)
	OP_1(jr_nz_n)
	OP_1(jr_c_n)
	OP_1(jr_nc_n)

	// RST
	OP_0(rst00)
	OP_0(rst08)
	OP_0(rst10)
	OP_0(rst18)
	OP_0(rst20)
	OP_0(rst28)
	OP_0(rst30)
	OP_0(rst38)

	//LD 8bit
	OP_0(ld_a_b)
	OP_0(ld_a_c)
	OP_0(ld_a_d)
	OP_0(ld_a_e)
	OP_0(ld_a_h)
	OP_0(ld_a_l)
	OP_0(ld_b_a)
	OP_0(ld_b_c)
	OP_0(ld_b_d)
	OP_0(ld_b_e)
	OP_0(ld_b_h)
	OP_0(ld_b_l)
	OP_0(ld_c_a)
	OP_0(ld_c_b)
	OP_0(ld_c_d)
	OP_0(ld_c_e)
	OP_0(ld_c_h)
	OP_0(ld_c_l)
	OP_0(ld_d_a)
	OP_0(ld_d_b)
	OP_0(ld_d_c)
	OP_0(ld_d_e)
	OP_0(ld_d_h)
	OP_0(ld_d_l)
	OP_0(ld_e_a)
	OP_0(ld_e_b)
	OP_0(ld_e_c)
	OP_0(ld_e_d)
	OP_0(ld_e_h)
	OP_0(ld_e_l)
	OP_0(ld_h_a)
	OP_0(ld_h_b)
	OP_0(ld_h_c)
	OP_0(ld_h_d)
	OP_0(ld_h_e)
	OP_0(ld_h_l)
	OP_0(ld_l_a)
	OP_0(ld_l_b)
	OP_0(ld_l_c)
	OP_0(ld_l_d)
	OP_0(ld_l_e)
	OP_0(ld_l_h)

	OP_1(ld_a_n)
	OP_1(ld_b_n)
	OP_1(ld_c_n)
	OP_1(ld_d_n)
	OP_1(ld_e_n)
	OP_1(ld_f_n)
	OP_1(ld_h_n)
	OP_1(ld_l_n)

	OP_2(ld_bc_nn)
	OP_2(ld_de_nn)
	OP_2(ld_hl_nn)
	OP_2(ld_sp_nn)

	OP_2(ldi_hlp_a)
	OP_2(ldd_hlp_a)

	OP_1(ldh_n_a)
	OP_1(ldh_a_n)
	// XOR
	OP_0(xor_a)
	OP_0(xor_b)
	OP_0(xor_c)
	OP_0(xor_d)
	OP_0(xor_e)
	OP_0(xor_h)
	OP_0(xor_l)


	// CP
	OP_0(cp_a)
	OP_0(cp_b)
	OP_0(cp_c)
	OP_0(cp_d)
	OP_0(cp_e)
	OP_0(cp_h)
	OP_0(cp_l)
	static void op_cp_n(CCpu_LR35902 * cpu, uint8_t opcode);
	// INC + DEC
	OP_0(inc_a)
	OP_0(inc_b)
	OP_0(inc_c)
	OP_0(inc_d)
	OP_0(inc_e)
	OP_0(inc_h)
	OP_0(inc_l)
	OP_0(dec_a)
	OP_0(dec_b)
	OP_0(dec_c)
	OP_0(dec_d)
	OP_0(dec_e)
	OP_0(dec_h)
	OP_0(dec_l)
	OP_0(inc_bc)
	OP_0(inc_de)
	OP_0(inc_hl)
	OP_0(inc_sp)
	OP_0(dec_bc)
	OP_0(dec_de)
	OP_0(dec_hl)
	OP_0(dec_sp)
};
