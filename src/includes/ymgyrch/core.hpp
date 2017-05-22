#pragma once
#include <ymgyrch/system.hpp>
namespace Ymgyrch {
class Core {
public:
    System * current;
    void Init(System *);
    void Start();
    void Tick(double time);
};
};

extern Ymgyrch::Core * g_core;