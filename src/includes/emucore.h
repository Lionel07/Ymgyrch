#pragma once
#include <ymgyrch.h>
#include <vector>
namespace Ymgyrch {
	class Core
	{
	public:
		Ymgyrch::System * running_system = nullptr;
		bool paused = false;
		bool stepping = false;

		Config::Systems system;
		std::string image_location = "";

		Core();
		void Init();
		void Start();
		void TickSystem();
	};

}
