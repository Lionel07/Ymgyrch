/********************************************************************************
** Form generated from reading UI file 'debugger.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGGER_H
#define UI_DEBUGGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Debugger
{
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *higherPane;
    QTableWidget *dissassembly;
    QTableWidget *regTable;
    QHBoxLayout *lowerPane;
    QPlainTextEdit *emuLog;
    QVBoxLayout *emuControls;
    QPushButton *debugStart;
    QPushButton *stepButton;
    QCheckBox *updateDisplay;

    void setupUi(QWidget *Debugger)
    {
        if (Debugger->objectName().isEmpty())
            Debugger->setObjectName(QStringLiteral("Debugger"));
        Debugger->setWindowModality(Qt::NonModal);
        Debugger->resize(640, 480);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Debugger->sizePolicy().hasHeightForWidth());
        Debugger->setSizePolicy(sizePolicy);
        Debugger->setMinimumSize(QSize(0, 240));
        Debugger->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Fixedsys Excelsior 3.01"));
        font.setPointSize(12);
        font.setStyleStrategy(QFont::NoAntialias);
        Debugger->setFont(font);
        mainLayout = new QVBoxLayout(Debugger);
        mainLayout->setSpacing(0);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        higherPane = new QHBoxLayout();
        higherPane->setSpacing(0);
        higherPane->setObjectName(QStringLiteral("higherPane"));
        dissassembly = new QTableWidget(Debugger);
        if (dissassembly->columnCount() < 2)
            dissassembly->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        dissassembly->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        dissassembly->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        dissassembly->setObjectName(QStringLiteral("dissassembly"));
        dissassembly->setFrameShape(QFrame::WinPanel);
        dissassembly->horizontalHeader()->setStretchLastSection(true);
        dissassembly->verticalHeader()->setVisible(false);

        higherPane->addWidget(dissassembly);

        regTable = new QTableWidget(Debugger);
        if (regTable->columnCount() < 3)
            regTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        regTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        regTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        regTable->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        if (regTable->rowCount() < 1)
            regTable->setRowCount(1);
        regTable->setObjectName(QStringLiteral("regTable"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(regTable->sizePolicy().hasHeightForWidth());
        regTable->setSizePolicy(sizePolicy1);
        regTable->setMinimumSize(QSize(0, 0));
        regTable->setMaximumSize(QSize(200, 16777215));
        regTable->setFrameShape(QFrame::WinPanel);
        regTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        regTable->setTabKeyNavigation(false);
        regTable->setProperty("showDropIndicator", QVariant(false));
        regTable->setDragDropOverwriteMode(false);
        regTable->setAlternatingRowColors(true);
        regTable->setSelectionMode(QAbstractItemView::NoSelection);
        regTable->setShowGrid(false);
        regTable->setRowCount(1);
        regTable->horizontalHeader()->setVisible(true);
        regTable->horizontalHeader()->setCascadingSectionResizes(false);
        regTable->horizontalHeader()->setDefaultSectionSize(50);
        regTable->horizontalHeader()->setHighlightSections(false);
        regTable->horizontalHeader()->setMinimumSectionSize(28);
        regTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        regTable->horizontalHeader()->setStretchLastSection(true);
        regTable->verticalHeader()->setVisible(false);
        regTable->verticalHeader()->setStretchLastSection(false);

        higherPane->addWidget(regTable);


        mainLayout->addLayout(higherPane);

        lowerPane = new QHBoxLayout();
        lowerPane->setSpacing(0);
        lowerPane->setObjectName(QStringLiteral("lowerPane"));
        emuLog = new QPlainTextEdit(Debugger);
        emuLog->setObjectName(QStringLiteral("emuLog"));
        emuLog->setMaximumSize(QSize(16777215, 200));
        QFont font1;
        font1.setFamily(QStringLiteral("Fixedsys Excelsior 3.01"));
        font1.setPointSize(12);
        emuLog->setFont(font1);
        emuLog->setFrameShape(QFrame::Box);
        emuLog->setReadOnly(true);

        lowerPane->addWidget(emuLog);

        emuControls = new QVBoxLayout();
        emuControls->setSpacing(0);
        emuControls->setObjectName(QStringLiteral("emuControls"));
        debugStart = new QPushButton(Debugger);
        debugStart->setObjectName(QStringLiteral("debugStart"));

        emuControls->addWidget(debugStart);

        stepButton = new QPushButton(Debugger);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setMinimumSize(QSize(0, 0));

        emuControls->addWidget(stepButton);

        updateDisplay = new QCheckBox(Debugger);
        updateDisplay->setObjectName(QStringLiteral("updateDisplay"));

        emuControls->addWidget(updateDisplay);


        lowerPane->addLayout(emuControls);


        mainLayout->addLayout(lowerPane);


        retranslateUi(Debugger);

        QMetaObject::connectSlotsByName(Debugger);
    } // setupUi

    void retranslateUi(QWidget *Debugger)
    {
        Debugger->setWindowTitle(QApplication::translate("Debugger", "Ymgyrch Debugger", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = dissassembly->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Debugger", "Address", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = dissassembly->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Debugger", "Dissassembly", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = regTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("Debugger", "Reg", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = regTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("Debugger", "Value", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = regTable->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("Debugger", "Type", Q_NULLPTR));
        emuLog->setPlainText(QApplication::translate("Debugger", "Log\n"
"", Q_NULLPTR));
        debugStart->setText(QApplication::translate("Debugger", "Start CPU", Q_NULLPTR));
        stepButton->setText(QApplication::translate("Debugger", "Step", Q_NULLPTR));
        updateDisplay->setText(QApplication::translate("Debugger", "Update Debug Display", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Debugger: public Ui_Debugger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGGER_H
