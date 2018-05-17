#include "random.h"

#include <random>
#include <chrono>

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

void random::setRandomSeed(const std::string & seed)
{
	std::seed_seq seedSeq(seed.cbegin(), seed.cend());

	randomGenerator().seed(seedSeq);
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