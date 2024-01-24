#include "HexViewBrowser.h"

HexViewBrowser::HexViewBrowser(QWidget* parent)
	: QListView(parent), model(new QStringListModel(this))
{
	setUniformItemSizes(true);

	setModel(model);

	setSelectionMode(QAbstractItemView::ExtendedSelection);

	worker = new HexViewWorker();
	worker->moveToThread(&workerThread);

	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &HexViewBrowser::beginHexView, worker, &HexViewWorker::start, Qt::QueuedConnection);
	connect(worker, &HexViewWorker::hexViewTextUpdate, this, &HexViewBrowser::hexViewTextUpdate, Qt::QueuedConnection);

	workerThread.start();
}

HexViewBrowser::~HexViewBrowser()
{
	workerThread.quit();
	workerThread.wait();
}

void HexViewBrowser::loadHexView(const QString& filePath)
{
	worker->setFilePath(filePath);
	emit beginHexView();
}

void HexViewBrowser::hexViewTextUpdate(const QString& textChunk)
{
	QStringList lines = textChunk.split('\n');
	QStringList existingLines = model->stringList();

	existingLines.append(lines);
	model->setStringList(existingLines);
}

