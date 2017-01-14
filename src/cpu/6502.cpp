#include <cpu/6502.h>
#include <log.h>

CPU_6502::CPU_6502(EmuSystem * sys) : Cpu(sys)
{
	setName("CPU0 (6502)");
	g_log->Log(getName().c_str(), "Initialised");
}

CPU_6502::CPU_6502(EmuSystem * sys, Model model) : Cpu(sys)
{
	if (model == MODEL_2A03)
	{
		setName("2A03 (6502)");
	}
	else
	{
		setName("CPU0 (6502)");
	}
	
	g_log->Log(getName().c_str(), "Initialised");

	this->model = model;
}

void CPU_6502::Init() {
	regs.p = 0x34;
	regs.a = 0;
	regs.x = 0;
	regs.y = 0;
	regs.sp = 0xFD;
	regs.pc = 0xC000;
}

void CPU_6502::Tick() {

}
