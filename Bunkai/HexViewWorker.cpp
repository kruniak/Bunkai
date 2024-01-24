#include "HexViewWorker.h"

HexViewWorker::HexViewWorker()
	: timer(new QTimer(this))
{
	connect(timer, &QTimer::timeout, this, &HexViewWorker::processChunk);

	timer->setInterval(10);
}

void HexViewWorker::start()
{
	timer->start();
}

void HexViewWorker::processChunk()
{
	const size_t endOffset = std::min(offset + chunkSize, length);
	QString hexViewText;
	const uintptr_t runtimeAddr = 0x0000000000000000;

	for (; offset < endOffset; offset += 0x10)
	{
		QString line;
		line += QString::asprintf("%016" PRIX64 ":\t", runtimeAddr + offset);

		QString asciiRepresentation;

		for (int i = 0; i < 16; ++i)
		{
			const uint8_t byte = data[offset + i];
			line += QString::asprintf("%02x ", byte);

			if (byte >= 0x20 && byte <= 0x7E)
			{
				asciiRepresentation += static_cast<char>(byte);
			}
			else
			{
				asciiRepresentation += '.';
			}
		}

		line += '\t' + asciiRepresentation + '\n';
		hexViewText += line;
	}

	if (!hexViewText.isEmpty())
	{
		emit hexViewTextUpdate(hexViewText);
	}

	if (offset >= length)
	{
		timer->stop();
	}

	QThread::msleep(5);
}
