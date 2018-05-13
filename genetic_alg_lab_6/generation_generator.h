#pragma once

#include "basket.h"

class GenerationGenerator
{
	uint _generationSize = 20;
	uint _generatingGenerationSize = 40;

	double _mutationChange = 0.05;

	std::list<Basket> _currentGeneration;

	uint _startProductCount = 0;
	uint _endProductsCount = 10;

	uint _costLimit = 2000;

	double _weightLimit = 15;

public:
	void generateRandomGeneration();

	void toNextGeneration();

	std::list<Basket> currentGeneration() const;

	Basket theBest() const;

private:
	bool isInLimit(const Basket& basket) const;

	std::list<Basket> generateNextGeneration() const;
};