#include <QtCore/QCoreApplication>

#include "generation_generator.h"

#include <iostream>

void printBasket(const Basket& basket)
{
	std::wcout << "Basket contains: " << std::endl;

	auto items = basket.items();

	for (auto& item : items)
	{
		std::wcout << item.product.name().toStdWString() << ": " << item.count << std::endl;
	}

	std::wcout << std::endl << "Utility: " << basket.utility() << std::endl;
	std::wcout << "Cost: " << basket.cost() << std::endl;
	std::wcout << "Weight: " << basket.weight() << std::endl;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	GenerationGenerator generator;

	generator.generateRandomGeneration();

	std::cout << "First generation best utility: " << generator.theBest().utility() << std::endl;

	while (true)
	{
		char generateNext;

		std::cout << "Press Y to generate next generation" << std::endl;

		std::cin >> generateNext;

		if (generateNext != 'y')
			break;

		generator.toNextGeneration();
		
		std::cout << "Next generation best utility: " << generator.theBest().utility() << std::endl;
	}

	printBasket(generator.theBest());

	return a.exec();
}
