#include <cpu.h>
#include <string>

Cpu::Cpu(Ymgyrch::System * sys)
{
	this->sys = sys;
	setName("CPU?");
}

Cpu::~Cpu()
{
}

bool Cpu::cpuActive() {
	return isActive;
}

void Cpu::setName(std::string name)
{
	this->name = name;
}

std::string Cpu::getName()
{
	return this->name;
}

void Cpu::Init()
{
}

void Cpu::Start()
{
	isActive = true;
}

void Cpu::Stop()
{
	isActive = false;
}

void Cpu::Tick()
{
	if (!isActive) { return; }
}

void Cpu::Reset()
{
	Stop();
}

void Cpu::PrintRegs()
{
}

std::vector<cpu_reg_t> Cpu::GetRegs()
{
	return std::vector<cpu_reg_t>();
}

std::vector<cpu_instruction_t> Cpu::GetDissassembly()
{
	return std::vector<cpu_instruction_t>();
}