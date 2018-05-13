#include "product.h"

const QString& Product::name() const
{
	return _name;
}

double Product::utility(uint count) const
{
	double result = 0;
	double utility = _lstart;

	for (uint i = 0; i < count; ++i) {
		result += utility;
		utility -= _k;
	}

	return result;
}

uint Product::cost() const
{
	return _cost;
}

double Product::weight() const
{
	return _weight;
}

const QList<Product>& Product::defaultProducts()
{
	static QList<Product> products
	{//			lstart	k		cost	weight	name
		Product(10,		0.6,	49,		1,		"Milk"),
		Product(5,		0.7,	21,		0.6,	"Bread"),
		Product(9,		0.5,	60,		0.3,	"Eggs"),
		Product(3,		0.9,	50,		0.1,	"Tea"),
		Product(5,		0.4,	65,		1,		"Sugar"),
		Product(7,		0.45,	40,		0.3,	"Sour Cream"),
		Product(5,		0.8,	35,		0.25,	"Ice Cream"),
		Product(3,		0.5,	55,		1,		"Cola"),
		Product(2,		0.9,	80,		0.5,	"Beer"),
		Product(5,		0.75,	95,		1,		"Butter")
	};

	return products;
}