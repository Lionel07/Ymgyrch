#pragma once
#include <IVideoSystem.h>
#include <SDL.h>



class SDLSubsystem : public IVideoSystem {
private:
	SDL_Renderer * rend;
	SDL_Texture * mainbuff;
public:
	void Init();
	void Init(SDL_Window * win);
	void Render();
	void SetInternalSize(int x, int y, int b);
	void BlitPixel(int x, int y, vid_color_t color);
	void BlitTexture(std::vector<unsigned char> tex);
};