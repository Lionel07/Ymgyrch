#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSettings>
#include <emucore.h>
#include <debugger.h>
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
	Ui::MainWindow *ui = nullptr;
	QTimer * main_clock = nullptr;
	QTimer * log_clock = nullptr;
	EmuCore * emu = nullptr;
	Debugger * debug = nullptr;
	QSettings* registry = nullptr;
	void onInit();

public slots:
	void onFileLoad();
	void onEmulatorStart();
	void onEmulatorPause();
	void onEmulatorStep();
	void onEmulatorStop();
	void doUpdate();
	void onToggleDebugger(bool enable);
	void loadLastRom();
};

#endif // MAINWINDOW_H
