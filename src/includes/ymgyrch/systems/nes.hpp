#pragma once
#include <ymgyrch/system.hpp>
#include <string>
#include <cstdint>
#include <vector>

namespace Ymgyrch {
namespace Systems {
	class NES : public System {
	private:
		double time;
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
