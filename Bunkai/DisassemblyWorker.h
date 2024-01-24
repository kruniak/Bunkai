#pragma once

#include <algorithm>
#include <cinttypes>

#include <QString>
#include <QTimer>
#include <QFile>
#include <QThread>
#include <QIODevice>

#include <Zydis/Zydis.h>

#include "FileWorkerBase.h"

class DisassemblyWorker : public FileWorkerBase
{
	Q_OBJECT

public:
	DisassemblyWorker();

public slots:
	void start() override;

signals:
	void disassemblyTextUpdate(QString textChunk);

private:
	QTimer* timer;

	ZydisDecoder decoder;
	ZydisFormatter formatter;

protected:
	void processChunk() override;
};

