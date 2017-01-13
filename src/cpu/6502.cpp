#include <cpu/6502.h>
#include <log.h>

CPU_6502::CPU_6502(EmuSystem * sys) : Cpu(sys)
{
	setName("CPU0 (6502)");
	g_log->Log(getName().c_str(), "Initialised");
}

void CPU_6502::Init() {

}

void CPU_6502::Tick() {

}
