#define RLUTIL_USE_ANSI
#include <QFileDialog>
#include "mainwindow.h"
#include "debugger.h"
#include "ui_mainwindow.h"
#include <log.h>
#include <ymgyrch.h>
#include <ROMInfo.h>
#include <system/Gameboy.h>
#include <stdio.h>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>

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
	g_config = new EmuConfig();
	emu = new EmuCore();

	main_clock = new QTimer(this);
	log_clock = new QTimer(this);
	// Set configuration
	g_config->emulator.displayMode = EmuConfig::GUI;

	main_clock->setTimerType(Qt::PreciseTimer);
	connect(main_clock, &QTimer::timeout, this, &MainWindow::doUpdate);

	if (g_config->emulator.noGraphics) {
		ui->glDisplay->deleteLater();
	}

	if (g_config->emulator.debugDefault) {
		onToggleDebugger(true);
	}

}

void MainWindow::onEmulatorStart()
{
	if (emu->running_system != nullptr) {
		onEmulatorStop();
		return;
	}

	// Determine running system
	emu->running_system = LoadSystem(emu->system);

	if (emu->running_system == nullptr) {
		g_log->Debug("UI", "Failed. Unable to determine system to run.");
		onEmulatorStop();
		return;
	}

	emu->Init();
	emu->Start();
	main_clock->start(0);

	setWindowTitle(tr("Ymgyrch: ") + QString::fromStdString(emu->image_location));

//	ui->startEmuButton->setText("Stop");

}

void MainWindow::onEmulatorPause()
{
	emu->paused = !emu->paused;
}

void MainWindow::onEmulatorStep()
{

}

void MainWindow::onEmulatorStop()
{
	main_clock->stop();
	emu->running_system = nullptr;
}


void MainWindow::doUpdate()
{
	emu->TickSystem();
}

void MainWindow::onToggleDebugger(bool enable)
{
	if (enable) {
		if (debug == nullptr) {
			if (g_config->emulator.debuggerInline) {
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
			if (g_config->emulator.debuggerInline) {
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

	QString fileName;

	fileName = QFileDialog::getOpenFileName(this,
		tr("Open ROM image"), registry->value("ui/directories/openrom").toString(),
		tr("ROM Files (*.bin *.gb *.nes *.*)"));


	if (!fileName.isEmpty()) {
		QDir currentDir;
		registry->setValue("ui/directories/openrom", currentDir.absoluteFilePath(fileName));
		registry->setValue("emu/file/lastrom", currentDir.absoluteFilePath(fileName));
		registry->sync();
	}

	// Set the kind of emulator we're running here
	emu->image_location = fileName.toStdString();
	emu->system = YmgyrchUI::getSystemFromRom(emu->image_location);
}


void MainWindow::loadLastRom() {
	QString filename = registry->value("emu/file/lastrom").toString();

	if (filename.isEmpty()) { return; }

	emu->image_location = filename.toStdString();
	emu->system = YmgyrchUI::getSystemFromRom(emu->image_location);

}

