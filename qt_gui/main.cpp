#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	a.setApplicationName("ymgyrch");
	a.setOrganizationName("");
	a.setOrganizationDomain("");
    MainWindow w;
    w.show();

    return a.exec();
}
