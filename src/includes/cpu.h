#pragma once
#include <string>
#include "system.h"
class EmuSystem;

namespace Ymgyrch {
	enum CpuRegType {
		REG_NONE = 0,
		REG_GENERAL_PURPOSE,
		REG_IO,
		REG_MSR,
		REG_PROGRAM_COUNTER,
		REG_STACK_POINTER,
		REG_ACCUMULATOR,
		REG_FLAGS,
		REG_TIMER,
		REG_COMBINED
	};
};

typedef struct {
	std::string name;
	uint64_t value;
	int bytes;
	Ymgyrch::CpuRegType type;
} cpu_reg_t;

typedef struct {
	uint64_t address;
	std::string dissassembly;
} cpu_instruction_t;

/*! A generic CPU */
class Cpu {
private:
    std::string name;
	bool isActive = true;
protected:
	/// The system the CPU is running on.
    EmuSystem * sys = nullptr;
public:

	uint64_t instructions_total = 0;
	uint64_t instructions_last = 0;
	uint64_t ips = 0;

	/// Create a new CPU
	explicit Cpu(EmuSystem * sys);
	/// Create a new CPU with a name.
	explicit Cpu(EmuSystem * sys, const std::string name):sys(sys), name(name){};
    ~Cpu();

	/// Is the CPU active?
    bool cpuActive();
	/// Set the name
    void setName(std::string name);
	/// Get the name
    std::string getName();

	/// Init the CPU
    virtual void Init();
	/// Activate the CPU
    virtual void Start();
	/// Stop the CPU
    virtual void Stop();
	/// Tick. This is CPU dependant but usually is where instructions are run
    virtual void Tick();
	/// Reset the state of the CPU
    virtual void Reset();
	
	/// Prints Registers to log
	virtual void PrintRegs();
	/// Returns a list of debug strings, used in the debugger.
	virtual std::vector<cpu_reg_t> GetRegs();
	virtual std::vector<cpu_instruction_t> GetDissassembly();
};
