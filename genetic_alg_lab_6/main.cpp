#include "generation_generator.h"

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
	GenerationGenerator generator;

	generator.generateRandomGeneration();

	std::cout << "First generation best utility: " << generator.theBest().utility() << std::endl;

	while (true)
	{
		char generateNext;

		std::cout << "Insert Y to generate next generation" << std::endl;

		std::cin >> generateNext;

		if (generateNext != 'y')
			break;

		generator.toNextGeneration();
		
		std::cout << "Next generation best utility: " << generator.theBest().utility() << std::endl;
	}

	printBasket(generator.theBest());

	std::cout << "Insert any text and press enter to exit from program: ";

	std::string end;

	std::cin >> end;

	return 0;
}
