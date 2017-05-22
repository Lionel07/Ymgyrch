#pragma once
#include <ymgyrch/core.hpp>
#include <ymgyrch/time.hpp>
#include <logging.hpp>

Ymgyrch::Core * g_core;

void Ymgyrch::Core::Init(System * sys) {
	current = sys;
	g_log->Log("Core", "Init");
}
void Ymgyrch::Core::Start() {
	Time::reset();
	current->Init();
	current->Start();
	g_log->Log("Core", "Start");
}
void Ymgyrch::Core::Tick(double time) {
	current->Update();
}