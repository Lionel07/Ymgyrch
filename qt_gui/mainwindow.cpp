#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#define RLUTIL_USE_ANSI

#include <log.h>
#include <ymgyrch.h>
#include <stdio.h>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	onInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onInit()
{
	g_log = new Logger();
	g_log->bufferOutput = true;
	g_config = new EmuConfig();
}

void MainWindow::onFileLoad() {
	g_log->Debug("UI", "Loading Rom...");

	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open ROM image"), "", 
		tr("ROM Files (*.bin *.gb *.nes *.*)"));
}