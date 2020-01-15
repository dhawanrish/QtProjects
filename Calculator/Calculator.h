#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"
#include <QtWidgets/QPushButton>

class Calculator : public QMainWindow
{
	Q_OBJECT

public:
	Calculator(QWidget *parent = Q_NULLPTR);
	~Calculator();

private:
	Ui::Calculator *ui;
	double calcVal, memVal;
	bool divOp, mulOp, addOp, subOp, opPressed;

private slots:
	void funButtonNumPressed();
	void funButtonOpPressed();

	void funButtonEqualsPressed();

	void funButtonMemPressed();
	void funButtonMemPlusPressed();
	void funButtonMemMinusPressed();
	void funButtonClearPressed();
	void funButtonErasePressed();
	void funButtonSignPressed();
	void funButtonPercentPressed();
	void funButtonDecimalPressed();
};
