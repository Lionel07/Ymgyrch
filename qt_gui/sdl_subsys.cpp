#include "sdl_subsys.h"
#include <log.h>
#include <vector>
void SDLSubsystem::Init()
{
}

void SDLSubsystem::Init(SDL_Window * win)
{
	rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
}

void SDLSubsystem::Render()
{
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, mainbuff, NULL, NULL);
	SDL_RenderPresent(rend);
}

void SDLSubsystem::SetInternalSize(int x, int y, int b)
{
	internal_x = x;
	internal_y = y;
	internal_b = b;
	mainbuff = SDL_CreateTexture(rend, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, x, y);
}

void SDLSubsystem::BlitPixel(int x, int y, vid_color_t color)
{
}

void SDLSubsystem::BlitTexture(std::vector<unsigned char> tex)
{
	if (mainbuff == NULL) { return; }

	SDL_UpdateTexture
	(
		mainbuff,
		NULL,
		&tex[0],
		internal_x * 4
	);
}