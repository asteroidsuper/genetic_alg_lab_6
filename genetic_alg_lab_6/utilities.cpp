#include "utilities.h"

double randomDouble()
{
	return static_cast<double>(std::rand()) / RAND_MAX;
}

bool utilities::randomTrue(double change)
{
	return randomDouble() <= change;
}

int utilities::randomInRange(int start, int end)
{
	auto diff = (end > start)? (end - start) : (start - end);

	return start + (std::rand() % diff);
}