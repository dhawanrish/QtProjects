#include "NotepadDemo.h"

NotepadDemo::NotepadDemo(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::NotepadDemo)
{
	ui->setupUi(this);
	this->setCentralWidget(ui->textEdit);
	currFile = QString();
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(fnNew()));
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(fnOpen()));
	connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(fnSaveAs()));
	connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(fnCopy()));
	connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(fnCut()));
	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(fnExit()));
	connect(ui ->actionPaste, SIGNAL(triggered()), this, SLOT(fnPaste()));
	connect(ui ->actionPrint, SIGNAL(triggered()), this, SLOT(fnPrint()));
	connect(ui ->actionUndo, SIGNAL(triggered()), this, SLOT(fnUndo()));
	connect(ui ->actionRedo, SIGNAL(triggered()), this, SLOT(fnRedo()));
	connect(ui ->actionSave, SIGNAL(triggered()), this, SLOT(fnSave()));
}

NotepadDemo::~NotepadDemo()
{
	delete ui;
}

void NotepadDemo::fnNew()
{
	currFile.clear();
	ui->textEdit->setText(QString());
}

void NotepadDemo::fnOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open File");
	QFile file(fileName);
	currFile = fileName;

	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
		return;
	}

	setWindowTitle(fileName);
	QTextStream in(&file);
	QString text = in.readAll();
	ui->textEdit->setText(text);
	file.close();
}

void NotepadDemo::fnSaveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save As");
	QFile file(fileName);

	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
		return;
	}
	currFile = fileName;
	setWindowTitle(fileName);
	QTextStream out(&file);
	QString text = ui->textEdit->toPlainText();
	out << text;
	file.close();
}

void NotepadDemo::fnCopy()
{
	ui->textEdit->copy();
}

void NotepadDemo::fnCut()
{
	ui->textEdit->cut();
}

void NotepadDemo::fnPaste()
{
	ui->textEdit->paste();
}

void NotepadDemo::fnExit()
{
	QApplication::quit();
}

void NotepadDemo::fnPrint()
{
	QPrinter printer;
	printer.setPrinterName("Printer Name");
	QPrintDialog printDialog(&printer, this);
	if (printDialog.exec() == QDialog::Rejected)
	{
		QMessageBox::warning(this, "Warning", "Cannot Access Printer");
		return;
	}
	ui->textEdit->print(&printer);
}

void NotepadDemo::fnUndo()
{
	ui->textEdit->undo();
}

void NotepadDemo::fnRedo()
{
	ui->textEdit->redo();
}

void NotepadDemo::fnSave()
{
	QFile file;
	if (currFile.isEmpty())
	{
		QString fileName = QFileDialog::getSaveFileName(this, "Save");
		file.setFileName(fileName);

		if (!file.open(QFile::WriteOnly | QFile::Text))
		{
			QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
			return;
		}
		currFile = fileName;
		setWindowTitle(fileName);
	}
	else
	{
		file.setFileName(currFile);
		file.open(QFile::WriteOnly | QFile::Text);
	}
		
	QTextStream out(&file);
	QString text = ui->textEdit->toPlainText();
	out << text;
	file.close();
}