#include "generation_generator.h"

#include "utilities.h"

#include <map>

bool basketLess(const Basket& a, const Basket& b)
{
	return a.utility() < b.utility();
}

void GenerationGenerator::generateRandomGeneration()
{
	_currentGeneration.clear();

	while (_currentGeneration.count() < _generationSize)
	{
		auto basket = Basket::generateRandomBasket(_startProductCount, _endProductsCount);

		if (isInLimit(basket))
			_currentGeneration << basket;
	}
}

void GenerationGenerator::toNextGeneration()
{
	std::map<double, Basket> orderedAllBaskets;

	for (auto& basket : _currentGeneration)
		orderedAllBaskets[basket.utility()] = basket;

	auto nextGeneration = generateNextGeneration();

	for (auto& basket : nextGeneration)
		orderedAllBaskets[basket.utility()] = basket;

	while (orderedAllBaskets.size() > _generationSize)
		orderedAllBaskets.erase(orderedAllBaskets.begin());

	for (auto& item : orderedAllBaskets)
	{
		if (!utilities::randomTrue(_mutationChange))
			continue;

		auto mutatedBasket = item.second.mutate(_mutationChange);

		if (isInLimit(mutatedBasket))
			orderedAllBaskets[mutatedBasket.utility()] = mutatedBasket;
	}

	_currentGeneration.clear();

	for (auto& mapItem : orderedAllBaskets)
		_currentGeneration << mapItem.second;
}

QList<Basket> GenerationGenerator::generateNextGeneration() const
{
	if (_currentGeneration.count() < 2)
		return { };

	QList<Basket> generatingGeneration;

	while (generatingGeneration.count() < _generatingGenerationSize)
	{
		uint firstIndex = utilities::randomInRange(0, _currentGeneration.count() - 1);
		uint secondIndex = firstIndex;

		while (secondIndex == firstIndex) 
			secondIndex = utilities::randomInRange(0, _currentGeneration.count() - 1);

		auto& firstBasket = _currentGeneration[firstIndex];
		auto& secondBasket = _currentGeneration[secondIndex];

		auto basket = Basket::crossBaskets(firstBasket, secondBasket);

		if (isInLimit(basket))
			generatingGeneration << basket;
	}

	return generatingGeneration;
}

QList<Basket> GenerationGenerator::currentGeneration() const
{
	return _currentGeneration;
}

Basket GenerationGenerator::theBest() const
{
	auto iterOnMax = std::max_element(_currentGeneration.cbegin(), _currentGeneration.cend(), basketLess);

	if (iterOnMax != _currentGeneration.cend())
		return *iterOnMax;

	return Basket();
}

bool GenerationGenerator::isInLimit(const Basket & basket) const
{
	return basket.weight() <= _weightLimit && basket.cost() <= _costLimit;
}
