#include <cpu.h>
#include <string>

CCpu::CCpu(CSystem * sys)
{
	this->sys = sys;
	setName("CPU?");
}


CCpu::~CCpu()
{

}

bool CCpu::cpuActive() {
	return isActive;
}

void CCpu::setName(std::string name)
{
	this->name = name;
}

std::string CCpu::getName()
{
	return this->name;
}

void CCpu::Init()
{

}

void CCpu::Start()
{
	isActive = true;
}

void CCpu::Stop()
{
	isActive = false;
}

void CCpu::Tick()
{
	if (!isActive) { return; }
}

void CCpu::Reset()
{
	Stop();
}

void CCpu::PrintRegs()
{
}

std::vector<std::string> CCpu::GetRegStrings()
{
	return std::vector<std::string>();
}
