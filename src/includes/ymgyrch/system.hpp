#pragma once
#include <ymgyrch/cpu.hpp>
#include <ymgyrch/memory/controller.hpp>
#include <string>
#include <cstdint>
#include <vector>

namespace Ymgyrch {
class System {
public:
    std::string name;
    Memory::Controller * memController;
    std::vector<Cpu*> cpus;
public:
    double time;
    bool isActive = false;
    virtual void Init()  = 0;
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Update()  = 0;
    virtual void Reset() = 0;
};
}; // namespace Ymgyrch
