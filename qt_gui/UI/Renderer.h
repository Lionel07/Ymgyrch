#pragma once
#include <QWidget>
#include <QTimer>
#include <emucore.h>
#include <SDL.h>
#include "../sdl_subsys.h"

namespace Ui {
class Renderer;
}

class Renderer : public QWidget
{
    Q_OBJECT

private:
	Ui::Renderer *ui;
	SDL_Window * sdl_widget;
	SDLSubsystem * subsys;
	QTimer *  update;
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
public:
	Ymgyrch::Core * emu;

    explicit Renderer(QWidget *parent = 0);
	~Renderer();
	void Init();
public slots:
	void UpdateRenderer();
    
};
