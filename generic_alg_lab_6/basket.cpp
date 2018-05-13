#include "basket.h"

#include "utilities.h"

#include <QtCore/QRandomGenerator>

#define NAME_OF(token) #token

uint mutatedNumber(uint number)
{
	int num = number;

	num += utilities::randomInRange(-5, 5);

	return std::abs(num);
}

QList<Basket::Item> Basket::items() const
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

	QList<Item> productItems;

	for (auto& product : products)
		productItems << Item(product, randFunc());

	return Basket(productItems);
}

Basket Basket::crossBaskets(const Basket & first, const Basket & second)
{
	QList<Item> items;

	uint count = std::min(first._items.count(), second._items.count());

	for (uint i = 0; i < count; ++i)
	{
		auto& copyFrom = utilities::randomTrue(0.5)? first : second;

		items << copyFrom._items[i];
	}

	return Basket(items);
}

Basket::Basket(const QList<Item>& items) : _items(items)
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

	QList<Item> newItems;

	for (auto& item : _items)
	{
		if (utilities::randomTrue(change)) {
			newItems << Item(item.product, mutatedNumber(item.count));
		}
		else {
			newItems << item;
		}
	}

	return Basket(newItems);
}