/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_ROM;
    QAction *actionStart;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionSet_System;
    QAction *actionLog;
    QAction *actionDebugger;
    QAction *actionExit;
    QAction *actionLoad_Last_ROM;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *container;
    QVBoxLayout *emulatorMain;
    QOpenGLWidget *glDisplay;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuRun;
    QMenu *menuView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionLoad_ROM = new QAction(MainWindow);
        actionLoad_ROM->setObjectName(QStringLiteral("actionLoad_ROM"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionPause = new QAction(MainWindow);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionSet_System = new QAction(MainWindow);
        actionSet_System->setObjectName(QStringLiteral("actionSet_System"));
        actionLog = new QAction(MainWindow);
        actionLog->setObjectName(QStringLiteral("actionLog"));
        actionLog->setCheckable(true);
        actionDebugger = new QAction(MainWindow);
        actionDebugger->setObjectName(QStringLiteral("actionDebugger"));
        actionDebugger->setCheckable(true);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionLoad_Last_ROM = new QAction(MainWindow);
        actionLoad_Last_ROM->setObjectName(QStringLiteral("actionLoad_Last_ROM"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        container = new QVBoxLayout();
        container->setSpacing(2);
        container->setObjectName(QStringLiteral("container"));
        container->setSizeConstraint(QLayout::SetDefaultConstraint);
        emulatorMain = new QVBoxLayout();
        emulatorMain->setSpacing(6);
        emulatorMain->setObjectName(QStringLiteral("emulatorMain"));
        glDisplay = new QOpenGLWidget(centralWidget);
        glDisplay->setObjectName(QStringLiteral("glDisplay"));
        glDisplay->setMinimumSize(QSize(0, 0));
        glDisplay->setSizeIncrement(QSize(0, 0));
        glDisplay->setBaseSize(QSize(320, 240));

        emulatorMain->addWidget(glDisplay);


        container->addLayout(emulatorMain);


        verticalLayout->addLayout(container);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuRun = new QMenu(menuBar);
        menuRun->setObjectName(QStringLiteral("menuRun"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuRun->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionLoad_ROM);
        menuFile->addAction(actionLoad_Last_ROM);
        menuFile->addAction(actionExit);
        menuRun->addAction(actionStart);
        menuRun->addAction(actionPause);
        menuRun->addAction(actionStop);
        menuRun->addSeparator();
        menuRun->addAction(actionSet_System);
        menuView->addAction(actionLog);
        menuView->addAction(actionDebugger);

        retranslateUi(MainWindow);
        QObject::connect(actionLoad_ROM, SIGNAL(triggered()), MainWindow, SLOT(onFileLoad()));
        QObject::connect(actionDebugger, SIGNAL(toggled(bool)), MainWindow, SLOT(onToggleDebugger(bool)));
        QObject::connect(actionStart, SIGNAL(triggered()), MainWindow, SLOT(onEmulatorStart()));
        QObject::connect(actionPause, SIGNAL(triggered()), MainWindow, SLOT(onEmulatorPause()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionLoad_Last_ROM, SIGNAL(triggered()), MainWindow, SLOT(loadLastRom()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ymgyrch", Q_NULLPTR));
        actionLoad_ROM->setText(QApplication::translate("MainWindow", "Open ROM...", Q_NULLPTR));
        actionLoad_ROM->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        actionStart->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        actionStart->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionPause->setText(QApplication::translate("MainWindow", "Pause", Q_NULLPTR));
        actionPause->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", Q_NULLPTR));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
        actionStop->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
        actionSet_System->setText(QApplication::translate("MainWindow", "Set System...", Q_NULLPTR));
        actionSet_System->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
        actionLog->setText(QApplication::translate("MainWindow", "Log", Q_NULLPTR));
        actionLog->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", Q_NULLPTR));
        actionDebugger->setText(QApplication::translate("MainWindow", "Debugger", Q_NULLPTR));
        actionDebugger->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionLoad_Last_ROM->setText(QApplication::translate("MainWindow", "Load Last ROM", Q_NULLPTR));
        actionLoad_Last_ROM->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+O", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuRun->setTitle(QApplication::translate("MainWindow", "Run", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
