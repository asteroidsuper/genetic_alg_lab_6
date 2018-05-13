#include "generation_generator.h"

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

int main(int argc, char *argv[])
{
	random::setRandomSeed(256);

	GenerationGenerator generator;

	generator.generateRandomGeneration();

	double curBestUtility = generator.theBest().utility();

	std::cout << "First generation best utility: " << curBestUtility  << std::endl;

	const uint bestUtilityTimeToBreak = 100;

	uint curBestUtilityTime = 0;

	uint generatedGenerationCount = 1;

	while (curBestUtilityTime < bestUtilityTimeToBreak)
	{
		generator.toNextGeneration();
		
		generatedGenerationCount++;

		auto bestUtility = generator.theBest().utility();

		curBestUtilityTime++;

		if (bestUtility != curBestUtility) {
			curBestUtility = bestUtility;
			curBestUtilityTime = 0;
		}
	}

	std::cout << "Generated generation count: " << generatedGenerationCount << std::endl << std::endl;

	printBasket(generator.theBest());

	std::cout << "Insert any text and press enter to exit from program: ";

	std::string end;

	std::cin >> end;

	return 0;
}
