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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *emuControls;
    QGroupBox *controls;
    QHBoxLayout *horizontalLayout_3;
    QPlainTextEdit *emuLog;
    QLabel *ipsLabel;
    QVBoxLayout *verticalLayout_3;
    QPushButton *debugStart;
    QPushButton *stepButton;
    QSpacerItem *verticalSpacer;
    QGroupBox *settings;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *updateSpeedLabel;
    QSlider *updateSlider;

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
        emuControls = new QVBoxLayout();
        emuControls->setSpacing(0);
        emuControls->setObjectName(QStringLiteral("emuControls"));
        controls = new QGroupBox(Debugger);
        controls->setObjectName(QStringLiteral("controls"));
        horizontalLayout_3 = new QHBoxLayout(controls);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        emuLog = new QPlainTextEdit(controls);
        emuLog->setObjectName(QStringLiteral("emuLog"));
        emuLog->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Fixedsys Excelsior 3.01"));
        font.setPointSize(12);
        emuLog->setFont(font);
        emuLog->setFrameShape(QFrame::Box);
        emuLog->setReadOnly(true);

        horizontalLayout_3->addWidget(emuLog);

        ipsLabel = new QLabel(controls);
        ipsLabel->setObjectName(QStringLiteral("ipsLabel"));
        ipsLabel->setMinimumSize(QSize(75, 0));

        horizontalLayout_3->addWidget(ipsLabel);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        debugStart = new QPushButton(controls);
        debugStart->setObjectName(QStringLiteral("debugStart"));
        debugStart->setMinimumSize(QSize(100, 0));

        verticalLayout_3->addWidget(debugStart);

        stepButton = new QPushButton(controls);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(stepButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);


        emuControls->addWidget(controls);

        settings = new QGroupBox(Debugger);
        settings->setObjectName(QStringLiteral("settings"));
        verticalLayout_2 = new QVBoxLayout(settings);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        updateSpeedLabel = new QLabel(settings);
        updateSpeedLabel->setObjectName(QStringLiteral("updateSpeedLabel"));

        verticalLayout->addWidget(updateSpeedLabel);

        updateSlider = new QSlider(settings);
        updateSlider->setObjectName(QStringLiteral("updateSlider"));
        updateSlider->setMinimum(1);
        updateSlider->setMaximum(100);
        updateSlider->setPageStep(1);
        updateSlider->setValue(1);
        updateSlider->setTracking(false);
        updateSlider->setOrientation(Qt::Horizontal);
        updateSlider->setInvertedAppearance(true);
        updateSlider->setTickPosition(QSlider::TicksBelow);
        updateSlider->setTickInterval(5);

        verticalLayout->addWidget(updateSlider);


        verticalLayout_2->addLayout(verticalLayout);


        emuControls->addWidget(settings);


        lowerPane->addLayout(emuControls);


        mainLayout->addLayout(lowerPane);


        retranslateUi(Debugger);
        QObject::connect(updateSlider, SIGNAL(valueChanged(int)), Debugger, SLOT(OnSetUpdateSpeed(int)));
        QObject::connect(updateSlider, SIGNAL(sliderMoved(int)), Debugger, SLOT(OnSetUpdateSpeed(int)));

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
        controls->setTitle(QApplication::translate("Debugger", "Controls", Q_NULLPTR));
        emuLog->setPlainText(QApplication::translate("Debugger", "Log\n"
"", Q_NULLPTR));
        ipsLabel->setText(QApplication::translate("Debugger", "Delta: 0", Q_NULLPTR));
        debugStart->setText(QApplication::translate("Debugger", "Start CPU", Q_NULLPTR));
        stepButton->setText(QApplication::translate("Debugger", "Step", Q_NULLPTR));
        settings->setTitle(QApplication::translate("Debugger", "Settings", Q_NULLPTR));
        updateSpeedLabel->setText(QApplication::translate("Debugger", "Debugging Rate (higher = slower)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Debugger: public Ui_Debugger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGGER_H
