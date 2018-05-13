#pragma once

namespace random 
{	
	void setRandomSeed(uint seed);

	bool randomTrue(double change);

	int randomInRange(int start, int end);
}