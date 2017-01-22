#pragma once
#include <cpu.h>
#include <system.h>
#include <memory.h>

/*! The Chip8's CPU */
class CPU_Chip8 : public Cpu {
public:
	typedef struct registers {
		uint8_t v[16];
		
		uint16_t I;
		uint16_t pc;
		uint16_t sp;
		uint8_t timer_delay;
		uint8_t timer_sound;
	} regs_t;

	uint16_t stack[16];
	regs_t regs;
	void (*instructions[0xF])(CPU_Chip8*,uint16_t);

public:
	/// Creates a new Chip8 CPU
	explicit CPU_Chip8(Ymgyrch::System * sys);
	void Init();
	/// Logs the current instruction to the debug log
	std::string Dissassemble(uint16_t opcode);
	void Tick();
	virtual std::vector<cpu_reg_t> GetRegs();


	std::vector<cpu_instruction_t> GetDissassembly();

	// Opcodes
	static void op_0(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_1(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_2(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_3(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_4(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_5(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_6(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_7(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_8(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_9(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_A(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_B(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_C(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_D(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_E(CPU_Chip8 * cpu, uint16_t opcode);
	static void op_F(CPU_Chip8 * cpu, uint16_t opcode);
	void op_unknown(uint16_t opcode);
};
