#include <cpu/CHIP8Cpu.h>
#include <log.h>

CPU_Chip8::CPU_Chip8(EmuSystem * sys) : Cpu(sys)
{
	setName("CPU0");
	g_log->Log(getName().c_str(), "Initialised");
}

void CPU_Chip8::Init() {
	regs.pc = 0x200;
}


void CPU_Chip8::DissassembleAndLog(uint16_t opcode) {
	std::string dissassembly;
	uint8_t reg = (opcode & 0x0F00) >> 8;
	switch (opcode & 0xF000)
	{
	case 0x0000:
		dissassembly = "???";
		break;
	case 0x1000:
		dissassembly = fmt::format("jmp 0x{0:03X}", opcode & 0x0FFF);
		break;
	case 0x6000:
		dissassembly = fmt::format("set V{0:X} {1:02x}", (opcode & 0x0F00) >> 8, opcode & 0x00FF);
		break;
	default:
		dissassembly = "???";
		break;
	}

	g_log->Debug(getName().c_str(), "0x{0:03x}: ( 0x{2:04x} ) {1:s}", regs.pc, dissassembly, opcode);
}

void CPU_Chip8::Tick() {
	uint16_t opcode = sys->mem.ReadShort(regs.pc);
	//uint8_t operand_n;
	uint8_t reg = (opcode & 0x0F00) >> 8;
	uint8_t value;
	//uint16_t operand_nn;
	
	//DissassembleAndLog(opcode);

	switch (opcode & 0xF000)
	{
	case 0x1000:
		regs.pc = opcode & 0x0FFF;
		break;
	case 0x6000:
		value = opcode & 0x00FF;
		regs.v[reg] = value;
		regs.pc += 2;
		break;
	case 0xA000:
		regs.I = opcode & 0x0FFF;
		regs.pc += 2;
		break;
	case 0xB000:
		regs.pc = (opcode & 0x0FFF) + regs.v[0];
		break;


	default:
		g_log->Log(getName().c_str(), "Unimplemented opcode 0x{0:4X}", opcode);
		sys->Stop();
		return;
	}

	DissassembleAndLog(opcode);
}

std::vector<std::string> CPU_Chip8::GetRegStrings()
{
	std::vector<std::string> registers;
	for (int i = 0; i < 16; i++)
	{
		registers.push_back(fmt::format("V{0:X}: 0x{1:02x}", i, regs.v[i]));
	}

	return registers;
}
