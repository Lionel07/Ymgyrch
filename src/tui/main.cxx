#include <tui/tui.hpp>
#include <rlutil/rlutil.h>
#include <logging.hpp>
#include <ymgyrch/core.hpp>
#include <ymgyrch/state.hpp>
#include <ymgyrch/systems/nes.hpp>
int main() {
    g_tui = new TextUI();
	g_log = new Logger();
	g_core = new Ymgyrch::Core();

	Ymgyrch::System * sys = new Ymgyrch::Systems::NES();
	State::romImage = "D:\\ROMS\\NES\\DonkeyKong.nes";
	//State::romImage = "D:\\Developer\\NES\\test.nes";
	g_core->Init(sys);
	g_core->Start();

	while (g_core->current->isActive) {
		g_core->Tick(0.0);

		// Draw UI
		g_tui->Update();
		g_tui->Draw();
		//rlutil::msleep(16);
	}

	g_log->Log("Core", "Execution Ended. Press any key to quit");

	while (rlutil::nb_getch() == 0) {
		// Draw UI
		g_tui->Update();
		g_tui->Draw();
		//rlutil::msleep(16);
	}
	
    return 0;
}
