#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
	Ui::MainWindow *ui;
	void onInit();
public:
    explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void onFileLoad();
};

#endif // MAINWINDOW_H
