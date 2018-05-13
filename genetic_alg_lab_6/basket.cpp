#include "basket.h"

#include "random.h"

#define NAME_OF(token) #token

uint mutatedNumber(uint number)
{
	int num = number;

	num += random::randomInRange(-5, 5);

	return std::abs(num);
}

std::list<Basket::Item> Basket::items() const
{
	return _items;
}

Basket Basket::generateRandomBasket(uint startProducts, uint endProducts)
{
	if (endProducts < startProducts)
		throw std::runtime_error("Value of \"" NAME_OF(endProducts) "\" must be equal or greater than value of \"" NAME_OF(startProducts) "\"");

	uint diff = endProducts - startProducts;

	auto randFunc = [diff, startProducts]() -> uint {
		return startProducts + std::rand() % (diff + 1);
	};

	auto& products = Product::defaultProducts();

	std::list<Item> productItems;

	for (auto& product : products)
		productItems.push_back(Item(product, randFunc()));

	return Basket(std::move(productItems));
}

Basket Basket::crossBaskets(const Basket & first, const Basket & second)
{
	std::list<Item> items;

	auto firstIter = first._items.cbegin();
	auto firstEnd = first._items.cend();

	auto secondIter = second._items.cbegin();
	auto secondEnd = second._items.cend();

	for (; firstIter != firstEnd && secondIter != secondEnd; firstIter++, secondIter++)
	{
		auto& selectedItem = random::randomTrue(0.5)? *firstIter : *secondIter;

		items.push_back(selectedItem);
	}

	return Basket(std::move(items));
}

Basket::Basket(std::list<Item>&& items) : _items(std::move(items))
{ }

Basket::Basket() { }

double Basket::utility() const
{
	double result = 0;

	for (auto& item : _items)
	{
		result += item.product.utility(item.count);
	}

	return result;
}

double Basket::weight() const
{
	double result = 0;

	for (auto& item : _items)
	{
		result += item.product.weight() * item.count;
	}

	return result;
}

uint Basket::cost() const
{
	uint result = 0;
	
	for (auto& item : _items)
	{
		result += item.product.cost() * item.count;
	}

	return result;
}

Basket Basket::mutate(double change) const
{
	if (change < 0 || change > 1)
		throw std::runtime_error("Value of \"" NAME_OF(change) "\" must be inside range [0.1]");

	std::list<Item> newItems;

	for (auto& item : _items)
	{
		if (random::randomTrue(change)) {
			newItems.push_back(Item(item.product, mutatedNumber(item.count)));
		}
		else {
			newItems.push_back(item);
		}
	}

	return Basket(std::move(newItems));
}