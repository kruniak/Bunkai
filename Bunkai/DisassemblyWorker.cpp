#include "DisassemblyWorker.h"

DisassemblyWorker::DisassemblyWorker()
	: timer(new QTimer(this))
{
	// Initialize Zydis, only support x64 executables now.

	// We first need to parse file headers, check if they're executables,
	//	then determine architecture/executable format.
	ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

	// We want style to be configurable at some point
	ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

	connect(timer, &QTimer::timeout, this, &DisassemblyWorker::processChunk);

	timer->setInterval(10);
}

void DisassemblyWorker::start()
{
	timer->start();
}

void DisassemblyWorker::processChunk()
{
	size_t endOffset = std::min(offset + chunkSize, length);
	QString disassemblyText;
	ZydisDecodedInstruction instr;
	ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
	ZyanU64 runtime_addr = 0x0000000000000000;

	while (offset < endOffset)
	{
		char buf[256];
		sprintf(buf, "%016" PRIX64 ":\t", runtime_addr + offset);
		disassemblyText += buf;

		if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, data + offset, length - offset, &instr, operands)))
		{
			disassemblyText += "??\n";
			offset++; // if decoding fails, increment by a single byte
		}
		else
		{
			ZydisFormatterFormatInstruction(&formatter, &instr, operands, instr.operand_count_visible, buf, sizeof(buf), runtime_addr, ZYAN_NULL);
			disassemblyText += buf;
			disassemblyText += '\n';
			offset += instr.length;
		}
	}

	if (!disassemblyText.isEmpty())
	{
		emit disassemblyTextUpdate(disassemblyText);
	}

	if (offset >= length)
	{
		timer->stop(); // stop the timer when done
	}

	QThread::msleep(5);
}

