#include <cpu/LR35902.h>
#include <log.h>
#include <string>
#include <libfmt/fmt/format.h>
#include <ymgyrch.h>

#define LR35902CPU_TEACH(num, arglength, name, qqqq) instructions[##num] = {##name, ##arglength, &CPU_LR35902::op_##qqqq}
#define LR35902CPU_TEACH_LD_N(num, reg0, reg1) LR35902CPU_TEACH(num, 0, "ld " #reg0 ", " #reg1, ld_## reg0##_##reg1)
#define LR35902CPU_TEACH_LD_NL(num, reg0) LR35902CPU_TEACH(num, 1, "ld " #reg0 ", 0x%02x" , ld_## reg0##_n)
#define LR35902CPU_TEACH_LD_NNL(num, reg0) LR35902CPU_TEACH(num, 2, "ld " #reg0 ", 0x%04x" , ld_## reg0##_nn)

CPU_LR35902::CPU_LR35902(EmuSystem * sys) : Cpu(sys)
{
	setName("CPU0");
	g_log->Log(getName().c_str(), "Initialised");
	memset(&instructions, 0, 256 * sizeof(cpu_instruction_t));
	next_opcode = 0x00;
	regs = {};
}

void CPU_LR35902::TeachInstructions() {
	if (firstTimeSetup == true) { return; }
	// Here, we setup our instructions
	// Unique instructions

	//Uniques
	LR35902CPU_TEACH(0x00, 0, "nop", nop);

	LR35902CPU_TEACH(0xE0, 1, "ldh (0xFF00 + 0x%x), A", ldh_n_a);
	LR35902CPU_TEACH(0xF0, 1, "ldh A, (0xFF00 + 0x%x)", ldh_a_n);


	//Jumps
	LR35902CPU_TEACH(0xC3, 2, "jp 0x%02X", jp_nn);
	LR35902CPU_TEACH(0x18, 1, "jr 0x%02X", jr_n);
	LR35902CPU_TEACH(0x28, 1, "jr z 0x%02X", jr_z_n);
	LR35902CPU_TEACH(0x38, 1, "jr c 0x%02X", jr_c_n);
	LR35902CPU_TEACH(0x20, 1, "jr nz 0x%02X", jr_nz_n);
	LR35902CPU_TEACH(0x30, 1, "jr nc 0x%02X", jr_nc_n);

	//Interrupts
	LR35902CPU_TEACH(0xFB, 0, "ei", ei);
	LR35902CPU_TEACH(0xF3, 0, "di", di);

	LR35902CPU_TEACH(0xC7, 0, "rst 0x00", rst00);
	LR35902CPU_TEACH(0xCF, 0, "rst 0x08", rst08);
	LR35902CPU_TEACH(0xD7, 0, "rst 0x10", rst10);
	LR35902CPU_TEACH(0xDF, 0, "rst 0x18", rst18);
	LR35902CPU_TEACH(0xE7, 0, "rst 0x20", rst20);
	LR35902CPU_TEACH(0xEF, 0, "rst 0x28", rst28);
	LR35902CPU_TEACH(0xF7, 0, "rst 0x30", rst30);
	LR35902CPU_TEACH(0xFF, 0, "rst 0x38", rst38);

	// Load 8bit reg
	LR35902CPU_TEACH(0x7F, 0, "ld a, a", nop);
	LR35902CPU_TEACH_LD_N(0x78, a, b);
	LR35902CPU_TEACH_LD_N(0x79, a, c);
	LR35902CPU_TEACH_LD_N(0x7A, a, d);
	LR35902CPU_TEACH_LD_N(0x7B, a, e);
	LR35902CPU_TEACH_LD_N(0x7C, a, h);
	LR35902CPU_TEACH_LD_N(0x7D, a, l);
	LR35902CPU_TEACH_LD_N(0x47, b, a);
	LR35902CPU_TEACH(0x40, 0, "ld b, b", nop);
	LR35902CPU_TEACH_LD_N(0x41, b, c);
	LR35902CPU_TEACH_LD_N(0x42, b, d);
	LR35902CPU_TEACH_LD_N(0x43, b, e);
	LR35902CPU_TEACH_LD_N(0x44, b, h);
	LR35902CPU_TEACH_LD_N(0x45, b, l);
	LR35902CPU_TEACH_LD_N(0x4F, c, a);
	LR35902CPU_TEACH_LD_N(0x48, c, b);
	LR35902CPU_TEACH(0x49, 0, "ld c, c", nop);
	LR35902CPU_TEACH_LD_N(0x4A, c, d);
	LR35902CPU_TEACH_LD_N(0x4B, c, e);
	LR35902CPU_TEACH_LD_N(0x4C, c, h);
	LR35902CPU_TEACH_LD_N(0x4D, c, l);
	LR35902CPU_TEACH_LD_N(0x57, d, a);
	LR35902CPU_TEACH_LD_N(0x50, d, b);
	LR35902CPU_TEACH_LD_N(0x51, d, c);
	LR35902CPU_TEACH(0x52, 0, "ld d, d", nop);
	LR35902CPU_TEACH_LD_N(0x53, d, e);
	LR35902CPU_TEACH_LD_N(0x54, d, h);
	LR35902CPU_TEACH_LD_N(0x55, d, l);
	LR35902CPU_TEACH_LD_N(0x5F, e, a);
	LR35902CPU_TEACH_LD_N(0x58, e, b);
	LR35902CPU_TEACH_LD_N(0x59, e, c);
	LR35902CPU_TEACH_LD_N(0x5A, e, d);
	LR35902CPU_TEACH(0x5B, 0, "ld e, e", nop);
	LR35902CPU_TEACH_LD_N(0x5C, e, h);
	LR35902CPU_TEACH_LD_N(0x5D, e, l);
	LR35902CPU_TEACH_LD_N(0x67, h, a);
	LR35902CPU_TEACH_LD_N(0x60, h, b);
	LR35902CPU_TEACH_LD_N(0x61, h, c);
	LR35902CPU_TEACH_LD_N(0x62, h, d);
	LR35902CPU_TEACH_LD_N(0x63, h, e);
	LR35902CPU_TEACH(0x64, 0, "ld h, h", nop);
	LR35902CPU_TEACH_LD_N(0x65, h, l);
	LR35902CPU_TEACH_LD_N(0x6F, l, a);
	LR35902CPU_TEACH_LD_N(0x68, l, b);
	LR35902CPU_TEACH_LD_N(0x69, l, c);
	LR35902CPU_TEACH_LD_N(0x6A, l, d);
	LR35902CPU_TEACH_LD_N(0x6B, l, e);
	LR35902CPU_TEACH_LD_N(0x6C, l, h);
	LR35902CPU_TEACH(0x6D, 0, "ld l, l", nop);
	LR35902CPU_TEACH_LD_NL(0x3E, a);
	LR35902CPU_TEACH_LD_NL(0x06, b);
	LR35902CPU_TEACH_LD_NL(0x0E, c);
	LR35902CPU_TEACH_LD_NL(0x16, d);
	LR35902CPU_TEACH_LD_NL(0x1E, e);
	LR35902CPU_TEACH_LD_NL(0x26, h);
	LR35902CPU_TEACH_LD_NL(0x2E, l);

	// Load NN
	LR35902CPU_TEACH_LD_NNL(0x01, bc);
	LR35902CPU_TEACH_LD_NNL(0x11, de);
	LR35902CPU_TEACH_LD_NNL(0x21, hl);
	LR35902CPU_TEACH_LD_NNL(0x31, sp);
	LR35902CPU_TEACH(0xEA, 0, "ld (nn), a", ld_nn_a);
	LR35902CPU_TEACH(0x22, 0, "ldi (hl), a", ldi_hlp_a);
	LR35902CPU_TEACH(0x32, 0, "ldd (hl), a", ldd_hlp_a);

	//XOR
	LR35902CPU_TEACH(0xAF, 0, "xor a", xor_a);
	LR35902CPU_TEACH(0xA8, 0, "xor b", xor_b);
	LR35902CPU_TEACH(0xA9, 0, "xor c", xor_c);
	LR35902CPU_TEACH(0xAA, 0, "xor d", xor_d);
	LR35902CPU_TEACH(0xAB, 0, "xor e", xor_e);
	LR35902CPU_TEACH(0xAC, 0, "xor h", xor_h);
	LR35902CPU_TEACH(0xAD, 0, "xor l", xor_l);

	//CP
	LR35902CPU_TEACH(0xBF, 0, "cp a", cp_a);
	LR35902CPU_TEACH(0xB8, 0, "cp b", cp_b);
	LR35902CPU_TEACH(0xB9, 0, "cp c", cp_c);
	LR35902CPU_TEACH(0xBA, 0, "cp d", cp_d);
	LR35902CPU_TEACH(0xBB, 0, "cp e", cp_e);
	LR35902CPU_TEACH(0xBC, 0, "cp h", cp_h);
	LR35902CPU_TEACH(0xBD, 0, "cp l", cp_l);
	LR35902CPU_TEACH(0xFE, 1, "cp n", cp_n);

	// INC and DEC
	LR35902CPU_TEACH(0x3C, 0, "inc a", inc_a);
	LR35902CPU_TEACH(0x04, 0, "inc b", inc_b);
	LR35902CPU_TEACH(0x0C, 0, "inc c", inc_c);
	LR35902CPU_TEACH(0x14, 0, "inc d", inc_d);
	LR35902CPU_TEACH(0x1C, 0, "inc e", inc_e);
	LR35902CPU_TEACH(0x24, 0, "inc h", inc_h);
	LR35902CPU_TEACH(0x2C, 0, "inc l", inc_l);
	LR35902CPU_TEACH(0x03, 0, "inc bc", inc_bc);
	LR35902CPU_TEACH(0x13, 0, "inc de", inc_de);
	LR35902CPU_TEACH(0x23, 0, "inc hl", inc_hl);
	LR35902CPU_TEACH(0x33, 0, "inc sp", inc_sp);

	LR35902CPU_TEACH(0x3D, 0, "dec a", dec_a);
	LR35902CPU_TEACH(0x05, 0, "dec b", dec_b);
	LR35902CPU_TEACH(0x0D, 0, "dec c", dec_c);
	LR35902CPU_TEACH(0x15, 0, "dec d", dec_d);
	LR35902CPU_TEACH(0x1D, 0, "dec e", dec_e);
	LR35902CPU_TEACH(0x25, 0, "dec h", dec_h);
	LR35902CPU_TEACH(0x2D, 0, "dec l", dec_l);
	LR35902CPU_TEACH(0x0B, 0, "dec bc", dec_bc);
	LR35902CPU_TEACH(0x1B, 0, "dec de", dec_de);
	LR35902CPU_TEACH(0x2B, 0, "dec hl", dec_hl);
	LR35902CPU_TEACH(0x3B, 0, "dec sp", dec_sp);



	// Reserved instructions
	LR35902CPU_TEACH(0xD3, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xDD, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xE3, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xE4, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xEB, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xEC, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xED, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xF2, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xF4, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xFC, 0, "RESERVED", reserved);
	LR35902CPU_TEACH(0xFD, 0, "RESERVED", reserved);
	firstTimeSetup = true;
}

void CPU_LR35902::Init() {
	regs.a = 0x01;
	regs.f = 0xB0;
	regs.bc = 0x0013;
	regs.de = 0x00D8;
	regs.hl = 0x014D;
	regs.sp = 0xFFFE;
	regs.pc = 0x100;
	regs.m = 0;
	regs.t = 0;
	flag_ime = false;
	TeachInstructions();
}

void CPU_LR35902::Tick() {
	if (!this->cpuActive()) { return; }
	FetchNext();
}

void CPU_LR35902::PrintRegs() {

}

std::vector<std::string> CPU_LR35902::GetRegStrings()
{
	std::vector<std::string> registers;
	std::deque<std::string>  dis;

	registers.push_back(fmt::format("A: 0x{0:02x} F: 0x{1:02x} | AF: 0x{2:04x} | PC: 0x{3:04x}", regs.a, regs.f, regs.af, regs.pc));
	registers.push_back(fmt::format("B: 0x{0:02x} C: 0x{1:02x} | BC: 0x{2:04x} | SP: 0x{3:04x}", regs.b, regs.c, regs.bc, regs.sp));
	registers.push_back(fmt::format("D: 0x{0:02x} E: 0x{1:02x} | DE: 0x{2:04x} | M : 0x{3:04x}", regs.d, regs.e, regs.de, regs.m));
	registers.push_back(fmt::format("H: 0x{0:02x} L: 0x{1:02x} | HL: 0x{2:04x} | T : 0x{3:04x}", regs.h, regs.l, regs.hl, regs.t));


	int prev_pc = regs.pc - lastInstructionLength;
	int prev_instructions = ((g_config->tui.rows - 3) / 2) - 3;
	int next_pc = regs.pc;
	
	bool attemptPastDissassemble = false;

	char * dis_string;

	if (!justJumped && attemptPastDissassemble)
	{
		for (int found_instructions = 0; found_instructions <= prev_instructions;)
		{
			bool found = false;
			// Take prev_pc, run back until diff + instructions[opcode].length would equal prev_pc
			// Set prev_pc to instruction
			// Repeat

			for (int j = 2; j > 0; j--)
			{
				uint64_t diff = prev_pc - j + 1;
				uint8_t canidate = sys->mem.ReadByte(diff);

				if (instructions[canidate].length + diff == prev_pc)
				{
					dis_string = DisassembleInstruction((uint16_t)diff);
					dis.push_front(fmt::format("|  0x{1:04x} : {0:25s}", dis_string, (uint16_t)diff));
					delete dis_string;

					found_instructions++;
					prev_pc -= j;
					found = true;
					break;
				}
			}

			if (!found)
			{
				prev_pc -= 1;
				dis.push_front(fmt::format("|  0x{0:04x} : 0x{1:02x}", prev_pc, sys->mem.ReadByte(prev_pc)));
				found_instructions++;
			}

		}
	}
	else
	{
		if (attemptPastDissassemble)
		{
			for (int i = 0; i <= prev_instructions; i++) {
				dis.push_front(fmt::format("|  0x{0:04x} : ???", prev_pc - i));
			}
		}
		else
		{
			prev_instructions = g_config->tui.rows - 8;
		}
		
	}
	
	dis_string = DisassembleInstruction(regs.pc);
	dis.push_back(fmt::format("|> 0x{1:04x} : {0:25s}", dis_string, regs.pc));
	delete dis_string;
	next_pc += instructions[sys->mem.ReadByte(next_pc)].length + 1;

	for (int i = 0; i <= prev_instructions; i++) {
		uint8_t opcode = sys->mem.ReadByte(next_pc);
		dis_string = DisassembleInstruction(next_pc);
		dis.push_back(fmt::format("|  0x{1:04x} : {0:25s}", dis_string, next_pc));
		delete dis_string;
		next_pc += instructions[opcode].length + 1;
	}
	
	for each (std::string line in dis)
	{
		registers.push_back(line);
	}

	return registers;
}

char * CPU_LR35902::DisassembleInstruction(uint16_t pc) {
	char instructionDis[256];
	char *instructionDissassembly = instructionDis;

	uint8_t opcode = sys->mem.ReadByte(pc);
	uint8_t operand8;
	uint16_t operand16;

	int count = 0;

	switch (instructions[opcode].length)
	{
	default:
	case 0:
		count = sprintf(instructionDissassembly, instructions[opcode].name.c_str());
		break;
	case 1:
		operand8 = sys->mem.ReadByte(pc + 1);
		count = sprintf(instructionDissassembly, instructions[opcode].name.c_str(), operand8);
		break;
	case 2:
		operand16 = sys->mem.ReadShort(pc + 1);
		count = sprintf(instructionDissassembly, instructions[opcode].name.c_str(), operand16);
		break;
	}

	if (count == 0)
	{
		count = sprintf(instructionDissassembly, "0x%x", opcode);
	}

	char * dis = new char[count + 1];
	memset(dis, 0, count + 1);
	memcpy(dis, instructionDissassembly, count);
	return dis;
}

void CPU_LR35902::FetchNext()
{
	uint8_t operand8;
	uint16_t operand16;
	next_opcode = sys->mem.ReadByte(regs.pc);
	justJumped = false;
	if (instructions[next_opcode].run == nullptr)
	{
		g_log->Log(getName().c_str(), "Opcode 0x{0:02X} is not implemented.", next_opcode);
		g_config->tui.showDebugger = true;
		sys->Stop();
		return;
	}

	regs.pc += instructions[next_opcode].length + 1;
	lastInstructionLength = instructions[next_opcode].length + 1;
	switch (instructions[next_opcode].length)
	{
	default:
	case 0:
		((void(*)(CPU_LR35902*))instructions[next_opcode].run)(this);
		break;
	case 1:
		operand8 = sys->mem.ReadByte(regs.pc - 1);
		((void(*)(CPU_LR35902*, uint8_t))instructions[next_opcode].run)(this, operand8);
		break;
	case 2:
		operand16 = sys->mem.ReadShort(regs.pc - 2);
		((void(*)(CPU_LR35902*, uint16_t))instructions[next_opcode].run)(this, operand16);
		break;
	}
}

// Instructions
void CPU_LR35902::xor (uint8_t num) {
	regs.a ^= num;
	if (regs.a) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	FLAGS_CLEAR(FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
}

void CPU_LR35902::rst(uint8_t num) {
	regs.sp -= 2;
	sys->mem.WriteWord(regs.sp, regs.pc);
	regs.pc = num;
}

uint16_t CPU_LR35902::inc(uint16_t value) {
	if ((value & 0x0f) == 0x0f) FLAGS_SET(FLAGS_HALFCARRY);
	else FLAGS_CLEAR(FLAGS_HALFCARRY);
	value++;
	if (value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	FLAGS_CLEAR(FLAGS_NEGATIVE);
	return value;
}

uint16_t CPU_LR35902::dec(uint16_t value) {
	if (value & 0x0f) FLAGS_CLEAR(FLAGS_HALFCARRY);
	else FLAGS_SET(FLAGS_HALFCARRY);
	value--;
	if (value) FLAGS_CLEAR(FLAGS_ZERO);
	else FLAGS_SET(FLAGS_ZERO);
	FLAGS_SET(FLAGS_NEGATIVE);
	return value;
}

void CPU_LR35902::cp(uint16_t value) {
	FLAGS_SET(FLAGS_NEGATIVE);
	char val = regs.a - value;
	if (val == 0) FLAGS_SET(FLAGS_ZERO);
	else FLAGS_CLEAR(FLAGS_ZERO);

	if (val > 0) FLAGS_SET(FLAGS_CARRY);
	else FLAGS_CLEAR(FLAGS_CARRY);

	if ((val & 0x0f) > (regs.a & 0x0f)) FLAGS_SET(FLAGS_HALFCARRY);
	else FLAGS_CLEAR(FLAGS_HALFCARRY);
}
