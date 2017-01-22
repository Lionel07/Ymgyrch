#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include <emucore.h>
#include "Debugger.h"
#include "Renderer.h"
#include <ymgyrch.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:

	bool needsRenderer = false;

	Ymgyrch::Core * emu = nullptr;
	Ui::MainWindow *ui = nullptr;
	QTimer * main_clock = nullptr;
	QTimer * sys_clock = nullptr;
	
	Debugger * debug = nullptr;
	Renderer * render = nullptr;
	QSettings* registry = nullptr;
	void onInit();

public slots:
	void onFileLoad();
	void onEmulatorStart();
	void onEmulatorPause();
	void onEmulatorStep();
	void onEmulatorStop();
	void doUpdate();
	void updateSystemClock();
	void onToggleDebugger(bool enable);
	void loadLastRom();
};

#endif // MAINWINDOW_H
