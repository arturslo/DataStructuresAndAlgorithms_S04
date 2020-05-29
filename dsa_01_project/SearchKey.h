#pragma once

using namespace std;

#include<tuple>

class SearchKey
{
public:
	const static int POSITION_NOT_FOUND = -1;

	static tuple<int, int> linearWoBarrier(int* array, int elementCount, int key);
	static tuple<int, int> approximationInOrderedArray(int* array, int elementCount, int key);
};
