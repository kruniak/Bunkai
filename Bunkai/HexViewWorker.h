#pragma once

#include <cinttypes>

#include <QString>
#include <QTimer>

#include "FileWorkerBase.h"

class HexViewWorker : public FileWorkerBase
{
	Q_OBJECT

public:
	HexViewWorker();

public slots:
	void start() override;

signals:
	void hexViewTextUpdate(QString textChunk);

private:
	QTimer* timer;

protected:
	void processChunk() override;
};
