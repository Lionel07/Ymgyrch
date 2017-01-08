#include <cpu/6502.h>
#include <log.h>

CCpu_6502::CCpu_6502(CSystem * sys) : CCpu(sys)
{
	setName("CPU0 (6502)");
	g_log->Log(getName().c_str(), "Initialised");
}

void CCpu_6502::Init() {

}

void CCpu_6502::Tick() {

}
