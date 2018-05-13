#include "random.h"

#include <random>

auto& randomGenerator()
{
	static std::mt19937 generator;
	return generator;
}

double randomDouble()
{
	std::uniform_real_distribution<double> dist;
	return dist(randomGenerator());
}

void random::setRandomSeed(uint seed)
{
	auto& generator = randomGenerator();
	generator.seed(seed);
}

bool random::randomTrue(double change)
{
	return randomDouble() <= change;
}

int random::randomInRange(int start, int end)
{
	std::uniform_int_distribution<int> dist(start, end);
	return dist(randomGenerator());
}