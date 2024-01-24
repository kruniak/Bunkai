#pragma once

#include <QListView>
#include <QThread>
#include <QStringListModel>

#include "HexViewWorker.h"

class HexViewBrowser : public QListView
{
	Q_OBJECT

public:
	HexViewBrowser(QWidget* parent = nullptr);
	~HexViewBrowser();

	void loadHexView(const QString& filePath);

signals:
	void beginHexView();

private slots:
	void hexViewTextUpdate(const QString& textChunk);

private:
	QStringListModel* model;
	QThread workerThread;
	HexViewWorker* worker;
};