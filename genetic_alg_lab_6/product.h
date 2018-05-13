#pragma once

class Product /// This is gen
{
	double _lstart;
	double _k;
	uint _cost;
	double _weight; // in kg
	std::string _name;

public:
	Product(double lstart, double k, uint cost, double weight, const std::string& name)
		: _lstart(lstart)
		, _k(k)
		, _cost(cost)
		, _weight(weight)
		, _name(name)
	{ }

	double utility(uint count) const;
	uint cost() const;
	double weight() const;

	std::string name() const;

	static const std::list<Product>& defaultProducts();
};