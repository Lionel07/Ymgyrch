#include <gpu.h>


class Chip8GPU : public EmuGpu {
public:

	uint8_t * frameBuffer;

	bool shouldDraw = true;


	void PlotPixel(int x, int y, bool on); 
	void DrawSprite(int x, int y, int h, uint16_t loc);
	void Tick();
	void Initialize();
	void Render();
	void Clear();
	void Reset();
};