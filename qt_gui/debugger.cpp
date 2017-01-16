#include "debugger.h"
#include "ui_debugger.h"
#include <cpu.h>
Debugger::Debugger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Debugger)
{
    ui->setupUi(this);
	clock = new QTimer(this);
	clock->setTimerType(Qt::CoarseTimer);
	connect(clock, &QTimer::timeout, this, &Debugger::DoUpdate);
	clock->start(g_config->debug.updateFrequency);

	tlog = new QTimer(this);
	tlog->setTimerType(Qt::CoarseTimer);
	connect(tlog, &QTimer::timeout, this, &Debugger::UpdateLog);
	tlog->start(250);

	ui->regTable->setColumnWidth(0, 30);
}

void Debugger::DoUpdate() {

	if (emu == nullptr) {
		return;
	}
	if (emu->running_system == nullptr) {
		return;
	}

	// Update Registers

	std::vector<cpu_reg_t> regs = emu->running_system->cpu[0]->GetRegs();
	std::vector<cpu_instruction_t> dis = emu->running_system->cpu[0]->GetDissassembly();
	ui->regTable->setRowCount((int)regs.size());
	int index = 0;
	for each (cpu_reg_t reg in regs) {
		QString name = QString::fromStdString(reg.name);
		QString type = "";

		std::string valformat;
		if (reg.bytes == 1) {
			valformat = "0x{0:02X}";
		}
		else
		{
			valformat = "0x{0:04X}";
		}

		QString value = QString::fromStdString(fmt::format(valformat, reg.value));
		
		switch (reg.type)
		{
		case Ymgyrch::REG_NONE:
			type = tr("");
			break;
		case Ymgyrch::REG_GENERAL_PURPOSE:
			type = tr("General");
			break;
		case Ymgyrch::REG_IO:
			type = tr("IO");
			break;
		case Ymgyrch::REG_MSR:
			type = tr("MSR");
			break;
		case Ymgyrch::REG_PROGRAM_COUNTER:
			type = tr("Program Counter");
			break;
		case Ymgyrch::REG_STACK_POINTER:
			type = tr("Stack Pointer");
			break;
		case Ymgyrch::REG_ACCUMULATOR:
			type = tr("Accumulator");
			break;
		case Ymgyrch::REG_FLAGS:
			type = tr("Flags");
			break;
		case Ymgyrch::REG_TIMER:
			type = tr("Timer");
			break;
		case Ymgyrch::REG_COMBINED:
			type = tr("Combined");
			break;
		default:
			break;
		}
		ui->regTable->setItem(index, 0, new QTableWidgetItem(name));
		ui->regTable->setItem(index, 1, new QTableWidgetItem(value));
		ui->regTable->setItem(index, 2, new QTableWidgetItem(type));
		index++;
	}


	g_config->debug.numToDissassemble = (ui->regTable->size().height() / 32)  + 1;


	// Now, display the dissassembly information in much the same way
	ui->dissassembly->setRowCount((int)dis.size());
	index = 0;
	for each (cpu_instruction_t instruction in dis) {
		QString addr = QString::fromStdString(fmt::format("0x{0:04x}", instruction.address));

		///@todo Show current PC somehow
		ui->dissassembly->setItem(index, 0, new QTableWidgetItem(addr));
		ui->dissassembly->setItem(index, 1, new QTableWidgetItem(QString::fromStdString(instruction.dissassembly)));
		index++;
	}
}

Debugger::~Debugger()
{
    delete ui;
}

void Debugger::UpdateLog()
{

	int numlines = 20;

	ui->emuLog->setPlainText("");

	int lower_limit = g_log->buffer.size() - numlines; ///@Todo replace with config limit

	if (lower_limit < 0) {
		lower_limit = 0;
	}

	for (int i = lower_limit; i < g_log->buffer.size(); i++) {
		ui->emuLog->appendPlainText(QString::fromStdString(g_log->buffer[i]));
	}

	g_log->FlushBufferToX(numlines);
}
