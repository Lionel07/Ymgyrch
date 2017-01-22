#define RLUTIL_USE_ANSI
#include <QCoreApplication>
#include <QFileDialog>
#include "MainWindow.h"
#include "Debugger.h"
#include "ui_mainwindow.h"
#include <log.h>
#include <ymgyrch.h>
#include <ROMInfo.h>
#include <system/Gameboy.h>
#include <stdio.h>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>
#include <gpu.h>
#include "../sdl_subsys.h"
#include <input.h>

#include "../sdl_input.h"
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	registry = new QSettings(QCoreApplication::applicationDirPath() + "/ymgyrch_qt.ini", QSettings::IniFormat);

	onInit();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onInit()
{
	g_log = new Logger();
	Ymgyrch::input = new Ymgyrch::InputManager();
	Ymgyrch::config = new Ymgyrch::Config();
	emu = new Ymgyrch::Core();

	main_clock = new QTimer(this);
	sys_clock = new QTimer(this);
	// Set configuration
	Ymgyrch::config->emulator.displayMode = Ymgyrch::Config::GUI;

	main_clock->setTimerType(Qt::PreciseTimer);
	connect(main_clock, &QTimer::timeout, this, &MainWindow::doUpdate);
	connect(sys_clock, &QTimer::timeout, this, &MainWindow::updateSystemClock);
	if (Ymgyrch::config->emulator.debugDefault) {
		onToggleDebugger(true);
	}
}

void MainWindow::onEmulatorStart()
{
	if (emu->running_system != nullptr) {
		onEmulatorStop();
	}

	// Determine running system
	emu->running_system = Ymgyrch::LoadSystem(emu->system);

	if (emu->running_system == nullptr) {
		g_log->Debug("UI", "Failed. Unable to determine system to run.");
		onEmulatorStop();
		return;
	}

	emu->Init();

	if (emu->running_system->config.needsGraphics) {
		if (render != nullptr) {
			ui->container->removeWidget(render);
			delete render;
		}

		render = new Renderer(this);
		ui->container->addWidget(render);

		emu->running_system->gpu->subsys = new SDLSubsystem();
		emu->running_system->gpu->backend = EmuGpu::SDL;

		render->emu = emu;
		render->Init();
		emu->running_system->gpu->Initialize();
	}

	if (emu->running_system->config.needsSeperateClock) {
		sys_clock->start(emu->running_system->config.seperateClockSpeed);
	}

	emu->Start();
	main_clock->start(0);

	setWindowTitle(tr("Ymgyrch: ") + QString::fromStdString(emu->image_location));
}

void MainWindow::onEmulatorPause()
{
	emu->paused = !emu->paused;
}

void MainWindow::onEmulatorStep()
{
	emu->stepping = true;
}

void MainWindow::onEmulatorStop()
{
	main_clock->stop();
	sys_clock->stop();
	delete emu->running_system;
	emu->running_system = nullptr;
}

void MainWindow::updateSystemClock()
{
	emu->running_system->SubTick();
}

void MainWindow::doUpdate()
{
	emu->TickSystem();
}

void MainWindow::onToggleDebugger(bool enable)
{
	if (enable) {
		if (debug == nullptr) {
			if (Ymgyrch::config->emulator.debuggerInline) {
				debug = new Debugger(this);
				ui->container->addWidget(debug);
			}
			else {
				debug = new Debugger();
				debug->show();
			}
			debug->emu = emu;
		}
	}
	else
	{
		if (debug != nullptr) {
			if (Ymgyrch::config->emulator.debuggerInline) {
				ui->container->removeWidget(debug);
			}
			else {
				debug->close();
			}
			debug = nullptr;
		}
	}
}

void MainWindow::onFileLoad() {
	g_log->Debug("UI", "Loading Rom...");

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open ROM image"), registry->value("last-opened-rom").toString(),
		tr("ROM Files (*.bin *.gb *.nes *.*)"));

	if (!fileName.isEmpty()) {
		QDir currentDir;
		registry->setValue("last-opened-rom", currentDir.absoluteFilePath(fileName));
		registry->sync();
	}
	else {
		return;
	}
	// Set the kind of emulator we're running here
	emu->image_location = fileName.toStdString();
	emu->system = YmgyrchUI::getSystemFromRom(emu->image_location);
}

void MainWindow::loadLastRom() {
	QString filename = registry->value("last-opened-rom").toString();

	if (filename.isEmpty()) { return; }

	emu->image_location = filename.toStdString();
	emu->system = YmgyrchUI::getSystemFromRom(emu->image_location);
}