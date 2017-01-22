#pragma once
#include <IInputSystem.h>
#include <input.h>

#include <SDL.h>


class SDLInput : public IInputSystem {
public:
	void Init();
	void Update();
};