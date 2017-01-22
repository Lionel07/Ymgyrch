#include <IInputSystem.h>
#include <input.h>
#include <sdl_input.h>
#include <log.h>
#include <SDL.h>
void SDLInput::Init() {
}

void SDLInput::Update() {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) // Process queue events
	{
		if (e.type == SDL_KEYDOWN) {
			parent->pressKey(e.key.keysym.sym);
		}
		else if (e.type == SDL_KEYUP) {
			parent->depressKey(e.key.keysym.sym);
		}
		else {
			continue;
		}
	}
}