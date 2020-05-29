#include "SearchKey.h"

tuple<int, int> SearchKey::linearWoBarrier(int* array, int elementCount, int key)
{
	int comparisonCount = 0;
	int keyPosition = POSITION_NOT_FOUND;
	for (int i = 0; i < elementCount; i++)
	{
		comparisonCount += 2;
		if (array[i] == key) {
			keyPosition = i;
			break;
		}
	}

	return make_tuple(keyPosition, comparisonCount);
}

tuple<int, int> SearchKey::approximationInOrderedArray(int* array, int elementCount, int key)
{
	// Start of index
	const int C = 0;
	int keyPosition = POSITION_NOT_FOUND;
	int comparisonCount = 0;

	int* firstElement = &array[C];
	int* lastElement = &array[elementCount + C - 1];

	comparisonCount += 2;
	if (key < *firstElement || key > * lastElement) {
		return make_tuple(keyPosition, comparisonCount);
	}

	int i = abs(
		round(
			elementCount * (key - *firstElement)
			/ (*lastElement - *firstElement + 1)
		)
	) + C;

	while (array[i] < key) { i++; comparisonCount++; }
	while (array[i] > key) { i--; comparisonCount++; }

	comparisonCount++;
	if (array[i] == key) {
		keyPosition = i;
	}

	return make_tuple(keyPosition, comparisonCount);
}
