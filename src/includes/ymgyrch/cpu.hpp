#pragma once
#include <string>
#include <cstdint>
#include <vector>

namespace Ymgyrch {

class System;

typedef struct cpu_instruction {
	uint64_t address;
	std::string dissassembly;
	bool current = false;
	bool endofreliable = false;
} cpu_instruction_t;

typedef struct cpu_info {
	std::string name;
	std::string data;
} cpu_info_t;

class Cpu {
protected:
    std::string name;
	Ymgyrch::System * sys;
public:
    struct stats {
        uint64_t ips = 0;
        uint64_t instructions_total = 0;
        uint64_t instructions_last = 0;
    } stats;
    bool isActive = false;
    virtual void Init(Ymgyrch::System * sys) = 0;
    virtual void Update()  = 0;
    virtual void Reset()   = 0;

	virtual std::vector<cpu_instruction_t> GetDissassembly() = 0;
	virtual std::vector<cpu_info_t> GetStatus() = 0;
};
}; // namespace Ymgyrch
