#pragma once

namespace random 
{	
	void setRandomSeed(uint seed);
	void setRandomSeed(const std::string& seed);

	bool randomTrue(double change);

	int randomInRange(int start, int end);
}