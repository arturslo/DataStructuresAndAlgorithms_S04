#pragma once

using namespace std;

#include <tuple>
#include <memory>

class RandomNumbers
{
public:
	static void seedTime();
	static int getInt(int rangeStart, int rangeEnd);
	static tuple<unique_ptr<int[]>, int> getUniqueIntArray(int rangeStart, int rangeEnd, int elementCount);
	static float getFloat(float min, float max);
};
