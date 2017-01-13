#include <system/NES.h>
#include <cpu/6502.h>
#include <log.h>
#include <mem/ram.h>
#include <mem/mirror_ram.h>
System_Nes::System_Nes() {
	this->name = "Nintendo Entertainment System";
}

void System_Nes::Init() {
	Cpu * cpu0 = new CPU_6502(this);

	cpu.push_back(cpu0);
	cpu0->Init();


	g_log->Log("NES", "Initialised");
}

void System_Nes::Start()
{
	isActive = true;
}

void System_Nes::Stop()
{
	isActive = false;
}

void System_Nes::Tick() {
	for each (Cpu * processor in cpu) {
		processor->Tick();
	}
}

void System_Nes::Reset()
{
	cpu.clear();
	Init();
}