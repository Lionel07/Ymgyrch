#pragma once
#include <system.h>

class CSys_NES : public CSystem {
public:
	CSys_NES();
	void Init();
	void Start();
	void Stop();
	void Tick();
	void Reset();
};