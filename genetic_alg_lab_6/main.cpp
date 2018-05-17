#include "genetic_engine.h"

#include "random.h"

#include <iostream>

void printBasket(const Basket& basket)
{
	std::cout << "Basket contains: " << std::endl;

	auto items = basket.items();

	for (auto& item : items)
	{
		std::cout << item.product.name() << ": " << item.count << std::endl;
	}

	std::cout << std::endl << "Utility: " << basket.utility() << std::endl;
	std::cout << "Cost: " << basket.cost() << std::endl;
	std::cout << "Weight: " << basket.weight() << std::endl;
}

double averageUtility(const GeneticEngine& engine)
{
	double utilitySum = 0;

	auto generation = engine.currentGeneration();

	for (auto& basket : generation)
		utilitySum += basket.utility();

	return utilitySum / generation.size();
}

void seedRandomGenerating()
{
	std::cout << "Enter seed: ";
	
	std::string seed;

	std::cin >> seed;

	random::setRandomSeed(seed);
}

int main(int argc, char *argv[])
{
	seedRandomGenerating();

	GeneticEngine engine;

	double curBestUtility = engine.theBest().utility();

	std::cout << std::endl;

	std::cout << "First generation best utility: " << curBestUtility << std::endl;
	std::cout << "Average utility: " << averageUtility(engine) << std::endl;

	const uint bestUtilityTimeToBreak = 100;

	uint curBestUtilityTime = 0;

	uint generatedGenerationCount = 1;

	while (curBestUtilityTime < bestUtilityTimeToBreak)
	{
		engine.toNextGeneration();
		
		generatedGenerationCount++;

		auto bestUtility = engine.theBest().utility();

		curBestUtilityTime++;

		if (bestUtility != curBestUtility) {
			curBestUtility = bestUtility;
			curBestUtilityTime = 0;
		}
	}

	std::cout << std::endl << std::endl;

	std::cout << "Generated generation count: " << generatedGenerationCount << std::endl << std::endl;

	printBasket(engine.theBest());

	std::cout << "Average generation utility: " << averageUtility(engine) << std::endl;

	std::cout << "Insert any text and press enter to exit from program: ";

	std::string end;

	std::cin >> end;

	return 0;
}