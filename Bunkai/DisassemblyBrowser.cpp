#include "DisassemblyBrowser.h"

DisassemblyBrowser::DisassemblyBrowser(QWidget* parent)
	: QListView(parent), model(new QStringListModel(this))
{
	setUniformItemSizes(true);
	// setLayoutMode(LayoutMode::Batched);

	setModel(model);

	setSelectionMode(QAbstractItemView::ExtendedSelection);

	worker = new DisassemblyWorker();
	worker->moveToThread(&workerThread);

	connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	connect(this, &DisassemblyBrowser::beginDisassembly, worker, &DisassemblyWorker::start, Qt::QueuedConnection);
	connect(worker, &DisassemblyWorker::disassemblyTextUpdate, this, &DisassemblyBrowser::disassemblyTextUpdate, Qt::QueuedConnection);

	workerThread.start();
}

DisassemblyBrowser::~DisassemblyBrowser()
{
	workerThread.quit();
	workerThread.wait();
}

void DisassemblyBrowser::loadDisassembly(const QString& filePath)
{
	worker->setFilePath(filePath);
	emit beginDisassembly();
}

void DisassemblyBrowser::disassemblyTextUpdate(const QString& textChunk)
{
	QStringList lines = textChunk.split('\n');
	QStringList existingLines = model->stringList();

	existingLines.append(lines);
	model->setStringList(existingLines);
}

void DisassemblyBrowser::contextMenuEvent(QContextMenuEvent* event)
{
	QModelIndex index = indexAt(event->pos());
	if (!index.isValid())
	{
		return;
	}

	QMenu contextMenu(this);
	QAction* copyAction = contextMenu.addAction(tr("Copy"));

	connect(copyAction, &QAction::triggered, this, &DisassemblyBrowser::copySelectedItems);
	contextMenu.exec(event->globalPos());
}

void DisassemblyBrowser::copySelectedItems()
{
	QStringList selectedTexts;
	QItemSelectionModel* selectionModel = this->selectionModel();
	QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
	for (const QModelIndex& index : selectedIndexes) {
		selectedTexts.append(model->data(index, Qt::DisplayRole).toString());
	}

	QString textToCopy = selectedTexts.join('\n');
	QClipboard* clipboard = QApplication::clipboard();
	clipboard->setText(textToCopy);
}

