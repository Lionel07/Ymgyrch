#include <input.h>
#include <IInputSystem.h>
#include <log.h>
Ymgyrch::InputManager * Ymgyrch::input;

void Ymgyrch::InputManager::mapNewKey(std::string keyname, int32_t keycode) {
	mappings[keycode] = keyname;
	keystatus[keyname] = false;
}
void Ymgyrch::InputManager::Update() {
	if (native_bindings == nullptr) { return; }
	native_bindings->Update();
}

void Ymgyrch::InputManager::pressKey(int32_t keycode) {
	if (mappings.count(keycode) == 0) {
		return;
	}

	keystatus[mappings[keycode]] = true;
}

void Ymgyrch::InputManager::depressKey(int32_t keycode) {
	if (mappings.count(keycode) == 0) {
		return;
	}

	keystatus[mappings[keycode]] = false;
}

bool Ymgyrch::InputManager::isKeyDown(std::string keyname) {
	return keystatus[keyname];
}

void Ymgyrch::InputManager::Reset() {
	mappings.clear();
}