#include "FileWorkerBase.h"

QString FileWorkerBase::filePath = "";
QByteArray FileWorkerBase::fileData;
const uint8_t* FileWorkerBase::data = nullptr;
size_t FileWorkerBase::length = 0;

void FileWorkerBase::initializeFileData(const QString& path)
{
	if (!fileData.isNull())
	{
		return;
	}

	QFile file(path);
	if (!file.open(QIODevice::ReadOnly))
	{
		return;
	}

	fileData = file.readAll();
	data = reinterpret_cast<const uint8_t*>(fileData.constData());
	length = fileData.size();
}

void FileWorkerBase::setFilePath(const QString& path)
{
	filePath = path;
	initializeFileData(path);
}

