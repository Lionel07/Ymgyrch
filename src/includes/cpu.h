#pragma once
#include <string>
#include "system.h"
class CSystem;
class CCpu {
private:
    std::string name;
    bool isActive = true;
protected:
    CSystem * sys = nullptr;
public:
	explicit CCpu(CSystem * sys);
	explicit CCpu(CSystem * sys, const std::string name):sys(sys), name(name){};
    ~CCpu();

    bool cpuActive();
    void setName(std::string name);
    std::string getName();

    virtual void Init();
    virtual void Start();
    virtual void Stop();
    virtual void Tick();
    virtual void Reset();
	
	virtual void PrintRegs();
	virtual std::vector<std::string> GetRegStrings();

};
