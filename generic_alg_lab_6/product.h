#pragma once

class Product /// This is gen
{
	double _lstart;
	double _k;
	uint _cost;
	double _weight; // in kg
	QString _name;

public:
	Product(double lstart, double k, uint cost, double weight, const QString& name)
		: _lstart(lstart)
		, _k(k)
		, _cost(cost)
		, _weight(weight)
		, _name(name)
	{ }

	double utility(uint count) const;
	uint cost() const;
	double weight() const;

	const QString& name() const;

	static const QList<Product>& defaultProducts();
};