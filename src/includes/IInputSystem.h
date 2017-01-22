#pragma once
#include <input.h>
#include <vector>

class IInputSystem {
public:
	Ymgyrch::InputManager * parent;
	virtual void Init() {};
	virtual void Update() {};
};