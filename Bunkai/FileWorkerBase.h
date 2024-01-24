#pragma once

#include <QObject>
#include <QString>
#include <QTimer>
#include <QFile>
#include <QByteArray>
#include <QIODevice>
#include <QThread>

class FileWorkerBase : public QObject
{
	Q_OBJECT

public:
	FileWorkerBase() = default;
	virtual ~FileWorkerBase() = default;

	virtual void start() = 0;

	static void initializeFileData(const QString& path);

public slots:
	static void setFilePath(const QString& path);

signals:
	void progressChanged(int progress);

protected:
	virtual void processChunk() = 0;

	static QString filePath;
	static QByteArray fileData;
	static const uint8_t* data;
	static size_t length;

	size_t offset = 0;

	const size_t chunkSize = 0x1000;
};

