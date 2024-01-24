#include "Bunkai.h"

#include <QFileDialog>

Bunkai::Bunkai(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// XXX: DEBUG
	ui.disassemblyBrowser->loadDisassembly("F:\\test.exe");
	ui.hexViewBrowser->loadHexView("F:\\test.exe");

	ui.tabWidget->setCurrentIndex(0);
}

Bunkai::~Bunkai()
{

}

void Bunkai::on_actionOpen_triggered()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "All files (*)");
	if (!filePath.isEmpty())
	{
		ui.disassemblyBrowser->loadDisassembly(filePath);
		ui.hexViewBrowser->loadHexView(filePath);

		// Show the disassembly tab
		ui.tabWidget->setCurrentIndex(0);
	}
}
