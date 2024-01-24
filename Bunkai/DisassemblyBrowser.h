#pragma once

#include <QListView>
#include <QString>
#include <QThread>
#include <QMenu>
#include <QMessageBox>
#include <QStringListModel>
#include <QContextMenuEvent>
#include <QAction>
#include <QApplication>
#include <QClipboard>

#include "DisassemblyWorker.h"

class DisassemblyBrowser : public QListView
{
	Q_OBJECT

public:
	DisassemblyBrowser(QWidget* parent = nullptr);
	~DisassemblyBrowser();

	void loadDisassembly(const QString& filePath);
	void contextMenuEvent(QContextMenuEvent* event);

signals:
	void beginDisassembly();

public slots:

private slots:
	void disassemblyTextUpdate(const QString& textChunk);
	void copySelectedItems();

private:
	QStringListModel* model;
	QThread workerThread;
	DisassemblyWorker* worker;
};

