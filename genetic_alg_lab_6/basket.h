#pragma once

#include "product.h"

class Basket /// This is chromosome
{
public:
	Basket();

	double utility() const;

	double weight() const;
	uint cost() const;
	
	Basket mutate(double change) const;

	struct Item
	{
		Item(const Product& product, uint count) 
			: product(product)
			, count(count)
		{ }

		Product product;
		uint count;
	};

	std::list<Item> items() const;

	static Basket generateRandomBasket(uint startProducts, uint endProducts);

	static Basket crossBaskets(const Basket& fisrt, const Basket& second);

private:
	Basket(std::list<Item>&& items);

	std::list<Item> _items;
};