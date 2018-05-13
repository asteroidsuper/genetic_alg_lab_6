#include "utilities.h"

#include <QtCore/qrandom.h>

QRandomGenerator& generator()
{
	static QRandomGenerator instance = QRandomGenerator::securelySeeded();

	return instance;
}

bool utilities::randomTrue(double change)
{
	return generator().generateDouble() <= change;
}

int utilities::randomInRange(int start, int end)
{
	return generator().bounded(start, end);
}