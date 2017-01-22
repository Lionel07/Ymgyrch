#pragma once
#include <string>
#include <unordered_map>

class IInputSystem;

namespace Ymgyrch {
	class InputManager {

	private:
		std::unordered_map<std::string, bool> keystatus;
		std::unordered_map<int32_t, std::string > mappings;
	public:
		IInputSystem * native_bindings;

		void Update();
		void Reset();


		void pressKey(int32_t keycode);
		void depressKey(int32_t keycode);

		void mapNewKey(std::string keyname, int32_t keycode);
		void mapKey(std::string keyname, int32_t default);
		bool isKeyDown(std::string keyname);
	};


	extern InputManager * input;
}