#pragma once
#include <vector>
#include "cpu.h"
#include <memcontroller.h>
class CCpu; //Prototype

class CSystem {
public:
	std::string name;
	bool isActive;

	std::vector<CCpu*> cpu;
	CMemController mem;

	virtual void Init();
	virtual void Start();
    virtual void Stop();
    virtual void Tick();
    virtual void Reset();
	virtual void LoadFile(std::string path);

	CSystem::~CSystem();
};