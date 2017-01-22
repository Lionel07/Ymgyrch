#include "renderer.h"
#include "ui_renderer.h"
#include <cpu.h>
#include <SDL.h>
#include <log.h>
#include <input.h>
#include <QKeyEvent>
Renderer::Renderer(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Renderer)
{
	ui->setupUi(this);
	show();

	sdl_widget = SDL_CreateWindowFrom((void*)ui->glWidget->winId());
	//sdl_widget = SDL_CreateWindow("Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, 0);
	if (!sdl_widget) {
		g_log->Error("Renderer", "SDL: failed to create window: {}", SDL_GetError());
	}
}

Renderer::~Renderer()
{
	delete ui;
}

void Renderer::UpdateRenderer() {
	subsys->Render();
}

void Renderer::Init()
{
	subsys = static_cast<SDLSubsystem*>(emu->running_system->gpu->subsys);
	subsys->Init(sdl_widget);

	update = new QTimer(this);
	update->setTimerType(Qt::PreciseTimer);
	connect(update, &QTimer::timeout, this, &Renderer::UpdateRenderer);
	update->start(16);
}

void Renderer::keyPressEvent(QKeyEvent *event)
{
	Ymgyrch::input->pressKey(event->key());
}
void Renderer::keyReleaseEvent(QKeyEvent *event) {
	Ymgyrch::input->depressKey(event->key());
}