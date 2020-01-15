#include "Calculator.h"

Calculator::Calculator(QWidget *parent): 
	QMainWindow(parent),
	ui(new Ui::Calculator)
{
	ui->setupUi(this);
	QPushButton* numButtons[10];
	for (int i = 0; i < 10; ++i)
	{
		QString butName = "button" + QString::number(i);
		numButtons[i] = Calculator::findChild<QPushButton*>(butName);
		connect(numButtons[i], SIGNAL(released()), this, SLOT(funButtonNumPressed()));
	}
	
	connect(ui->buttonPlus, SIGNAL(released()), this, SLOT(funButtonOpPressed()));
	connect(ui->buttonMinus, SIGNAL(released()), this, SLOT(funButtonOpPressed()));
	connect(ui->buttonMultiply, SIGNAL(released()), this, SLOT(funButtonOpPressed()));
	connect(ui->buttonDivide, SIGNAL(released()), this, SLOT(funButtonOpPressed()));
	connect(ui->buttonEquals, SIGNAL(released()), this, SLOT(funButtonEqualsPressed()));

	connect(ui->buttonMem, SIGNAL(released()), this, SLOT(funButtonMemPressed()));
	connect(ui->buttonMemPlus, SIGNAL(released()), this, SLOT(funButtonMemPlusPressed()));
	connect(ui->buttonMemMinus, SIGNAL(released()), this, SLOT(funButtonMemMinusPressed()));
	connect(ui->buttonClear, SIGNAL(released()), this, SLOT(funButtonClearPressed()));
	connect(ui->buttonErase, SIGNAL(released()), this, SLOT(funButtonErasePressed()));
	connect(ui->buttonSign, SIGNAL(released()), this, SLOT(funButtonSignPressed()));
	connect(ui->buttonPercent, SIGNAL(released()), this, SLOT(funButtonPercentPressed()));
	connect(ui->buttonDecimal, SIGNAL(released()), this, SLOT(funButtonDecimalPressed()));

	calcVal = 0.0;
	memVal = 0.0;
	ui->displayOut->setText(QString::number(calcVal));
	divOp = false;
	mulOp = false;
	addOp = false;
	subOp = false;
}

Calculator::~Calculator()
{
	delete ui;
}

void Calculator::funButtonNumPressed()
{
	QPushButton* button = (QPushButton*)sender();
	QString butVal = button->text();
	QString dispVal = ui->displayOut->text();
	if ((addOp || subOp || mulOp || divOp) && opPressed)
	{
		ui->displayOut->setText(butVal);
		opPressed = false;
	}
	else if ((dispVal.toDouble() == 0) || (dispVal.toDouble() == 0.0))
	{
		ui->displayOut->setText(butVal);
	}
	else
	{
		QString newVal = dispVal + butVal;
		double dblNewVal = newVal.toDouble();
		ui->displayOut->setText(QString::number(dblNewVal, 'g', 16));
	}
}

void Calculator::funButtonOpPressed()
{
	divOp = false;
	mulOp = false;
	addOp = false;
	subOp = false;
	opPressed = true;
	QString dispVal = ui->displayOut->text();
	calcVal = dispVal.toDouble();
	QPushButton* button = (QPushButton*)sender();
	QString butVal = button->text();
	if (QString::compare(butVal, "÷", Qt::CaseInsensitive) == 0)
		divOp = true;
	else if (QString::compare(butVal, "X", Qt::CaseInsensitive) == 0)
		mulOp = true;
	else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
		subOp = true;
	else
		addOp = true;
}

void Calculator::funButtonEqualsPressed()
{
	double result = 0.0;
	QString dispVal = ui->displayOut->text();
	double dblDispVal = dispVal.toDouble();
	if (addOp)
		result = calcVal + dblDispVal;
	else if (subOp)
		result = calcVal - dblDispVal;
	else if (mulOp)
		result = calcVal * dblDispVal;
	else if (divOp)
		result = calcVal / dblDispVal;
	ui->displayOut->setText(QString::number(result));
}

void Calculator::funButtonMemPressed()
{
	double result = 0.0;
	QString dispVal = ui->displayOut->text();
	memVal = dispVal.toDouble();
}

void Calculator::funButtonMemPlusPressed()
{
	double result = 0.0;
	QString dispVal = ui->displayOut->text();
	double dblDispVal = dispVal.toDouble();
	result = memVal + dblDispVal;
	ui->displayOut->setText(QString::number(result));
}

void Calculator::funButtonMemMinusPressed()
{
	double result = 0.0;
	QString dispVal = ui->displayOut->text();
	double dblDispVal = dispVal.toDouble();
	result = memVal - dblDispVal;
	ui->displayOut->setText(QString::number(result));
}

void Calculator::funButtonClearPressed()
{
	calcVal = 0.0;
	memVal = 0.0;
	ui->displayOut->setText(QString::number(calcVal));
	divOp = false;
	mulOp = false;
	addOp = false;
	subOp = false;
}

void Calculator::funButtonErasePressed()
{
	QString dispVal = ui->displayOut->text();

	if (dispVal.size() <= 1)
	{	
		ui->displayOut->setText("0");
	}
	else
	{
		QString newVal = dispVal.remove(-1, 1);
		ui->displayOut->setText(newVal);
	}
}

void Calculator::funButtonSignPressed()
{
	QString dispVal = ui->displayOut->text();
	QRegExp reg("[-][0-9.]*");
	if (reg.exactMatch(dispVal))
	{
		double dblDispVal = dispVal.toDouble();
		dblDispVal = -1 * dblDispVal;
		ui->displayOut->setText(QString::number(dblDispVal));
	}
}

void Calculator::funButtonPercentPressed()
{

}

void Calculator::funButtonDecimalPressed()
{

}

