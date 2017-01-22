#include "UI/mainwindow.h"
#include <QApplication>

#include <SDL.h>
#define USE_SDL

int main(int argc, char *argv[])
{
#ifdef USE_SDL
	SDL_Init(SDL_INIT_EVERYTHING);
#endif

	QApplication a(argc, argv);
	a.setApplicationName("ymgyrch");
	a.setOrganizationName("");
	a.setOrganizationDomain("");
	MainWindow w;
	w.show();

	int retval = a.exec();

#ifdef USE_SDL
	SDL_Quit();
#endif

	return retval;
}