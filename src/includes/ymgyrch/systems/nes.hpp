#pragma once
#include <ymgyrch/system.hpp>
#include <string>
#include <cstdint>
#include <vector>

//class Ymgyrch::Systems::NES_Mappers::Mapper;
#include <ymgyrch/systems/nes/nes_mapper.hpp>
namespace Ymgyrch {
namespace Systems {
	class NES : public System {
	private:
		double time;
		NES_Mappers::Mapper * cart;
	public:
		virtual void Init();
		void LoadRom();
		virtual void Start();
		virtual void Stop();
		virtual void Update();
		virtual void Reset();
	};
};
}; // namespace Ymgyrch
