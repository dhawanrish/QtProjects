#pragma once

#include <QtWidgets/QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include "ui_NotepadDemo.h"


class NotepadDemo : public QMainWindow
{
	Q_OBJECT

public:
	NotepadDemo(QWidget *parent = Q_NULLPTR);
	~NotepadDemo();

public slots:
	void fnNew();
	void fnOpen();
	void fnSaveAs();
	void fnCopy();
	void fnCut();
	void fnPaste();
	void fnExit();
	void fnPrint();
	void fnUndo();
	void fnRedo();
	void fnSave();

private:
	Ui::NotepadDemo *ui;
	QString currFile;
};
