#include "generation_generator.h"

#include "random.h"

#include <map>

template<class ContainerT>
auto& atIndex(ContainerT& container, size_t index)
{
	auto iter = std::begin(container);

	std::advance(iter, index);

	return *iter;
}

template<class ContainerT>
const auto& atIndex(const ContainerT& container, size_t index)
{
	auto iter = std::cbegin(container);

	std::advance(iter, index);

	return *iter;
}

bool basketLess(const Basket& a, const Basket& b)
{
	return a.utility() < b.utility();
}

void GenerationGenerator::generateRandomGeneration()
{
	_currentGeneration.clear();

	while (_currentGeneration.size() < _generationSize)
	{
		auto basket = Basket::generateRandomBasket(_startProductCount, _endProductsCount);

		if (isInLimit(basket))
			_currentGeneration.push_back(basket);
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
		if (!random::randomTrue(_mutationChange))
			continue;

		auto mutatedBasket = item.second.mutate(_mutationChange);

		if (isInLimit(mutatedBasket))
			orderedAllBaskets[mutatedBasket.utility()] = mutatedBasket;
	}

	_currentGeneration.clear();

	for (auto& mapItem : orderedAllBaskets)
		_currentGeneration.push_back(mapItem.second);
}

std::list<Basket> GenerationGenerator::generateNextGeneration() const
{
	if (_currentGeneration.size() < 2)
		return { };

	std::list<Basket> generatingGeneration;

	while (generatingGeneration.size() < _generatingGenerationSize)
	{
		uint firstIndex = random::randomInRange(0, (int)_currentGeneration.size() - 1);
		uint secondIndex = firstIndex;

		while (secondIndex == firstIndex) 
			secondIndex = random::randomInRange(0, (int)_currentGeneration.size() - 1);

		auto& firstBasket = atIndex(_currentGeneration, firstIndex);
		auto& secondBasket = atIndex(_currentGeneration, secondIndex);

		auto basket = Basket::crossBaskets(firstBasket, secondBasket);

		if (isInLimit(basket))
			generatingGeneration.push_back(basket);
	}

	return generatingGeneration;
}

std::list<Basket> GenerationGenerator::currentGeneration() const
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