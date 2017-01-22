#include <systems/chip8/Chip8GPU.h>
#include <cpu/CHIP8Cpu.h>
#include <log.h>
#include <ymgyrch.h>

void Chip8GPU::PlotPixel(int x, int y, bool on)
{
	frameBuffer[y * 64 + x] = 1;
	shouldDraw = true;
}

void Chip8GPU::DrawSprite(int x, int y, int h, uint16_t loc) {
	CPU_Chip8* cpu = static_cast<CPU_Chip8*>(sys->cpu[0]);

	for (int row = 0; row < h; row++) {
		uint8_t data = sys->mem.ReadByte(loc + row);

		for (int x_loc = 0; x_loc < 8; x_loc++) {
			if ((data & (0x80 >> x_loc)) != 0) {
				if (frameBuffer[(x + x_loc + ((y + row) * 64))] == 1) {
					cpu->regs.v[0xF] = 1;
				}

				frameBuffer[x + x_loc + ((y + row) * 64)] ^= 1;
			}
		}
	}
	shouldDraw = true;
}

void Chip8GPU::Tick()
{
}

void Chip8GPU::Initialize()
{
	frameBuffer = new uint8_t[64 * 32];
	memset(frameBuffer, 0, 64 * 32);
	//subsys->Init();
	subsys->SetInternalSize(64, 32, 1);
}

void Chip8GPU::Render()
{
	if (!shouldDraw) { return; }
	std::vector< unsigned char > pixels(64 * 32 * 4, 0);
	unsigned int offset = 0;
	for (unsigned int i = 0; i < 64 * 32; i++)
	{
		int val = frameBuffer[i] * 255;
		pixels[offset + 0] = val;
		pixels[offset + 1] = val;
		pixels[offset + 2] = val;
		pixels[offset + 3] = 0;
		offset += 4;
	}
	subsys->BlitTexture(pixels);
	shouldDraw = false;
}

void Chip8GPU::Clear()
{
}

void Chip8GPU::Reset()
{
}