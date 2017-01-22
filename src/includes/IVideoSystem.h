#pragma once
#include <stdint.h>
#include <vector>
typedef struct {
	uint32_t r;
	uint32_t g;
	uint32_t b;
} vid_color_t;


class IVideoSystem {

protected:
	int internal_x;
	int internal_y;
	int internal_b;

public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void SetInternalSize(int x, int y, int b) = 0;
	virtual void BlitPixel(int x, int y, vid_color_t color) = 0;
	virtual void BlitTexture(std::vector<unsigned char>) = 0;
};