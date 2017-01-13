#pragma once
#include <string>
#include "system.h"
class EmuSystem;


/*! A generic CPU */
class Cpu {
private:
    std::string name;
    bool isActive = true;
protected:
	/// The system the CPU is running on.
    EmuSystem * sys = nullptr;
public:

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
	virtual std::vector<std::string> GetRegStrings();

};
