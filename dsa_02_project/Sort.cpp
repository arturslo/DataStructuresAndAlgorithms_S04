#include "Sort.h"
#include <utility>

int Sort::bubbleSort(int* array, int elementCount)
{
	int* leftElement;
	int* rightElement;
	int temp;
	int comparisonCount = 0;

	for (int ltrIndex = 1; ltrIndex < elementCount; ltrIndex++)
	{
		comparisonCount++;

		for (int rtlIndex = elementCount - 1; rtlIndex >= ltrIndex; rtlIndex--)
		{
			comparisonCount += 2;

			leftElement = &array[rtlIndex - 1];
			rightElement = &array[rtlIndex];

			if (*leftElement > * rightElement) {
				temp = *rightElement;
				*rightElement = *leftElement;
				*leftElement = temp;
			}
		}
	}

	return comparisonCount;
}

int Sort::innerQuickSort(int left, int right, int* array)
{
	int comparisonCount = 0;
	int i = left;
	int j = right;
	int x = array[(left + right) / 2];

	do
	{
		while (array[i] < x) { i++; comparisonCount++; }
		while (x < array[j]) { j--; comparisonCount++; }

		comparisonCount++;
		if (i <= j)
		{
			swap(array[i], array[j]);
			i++;
			j--;
		}

		comparisonCount++;
	} while (i <= j);

	comparisonCount += 2;
	if (left < j) { comparisonCount += Sort::innerQuickSort(left, j, array); }
	if (i < right) { comparisonCount+= Sort::innerQuickSort(i, right, array); }

	return comparisonCount;
}

int Sort::quickSort(int* array, int elementCount)
{
	return Sort::innerQuickSort(0, elementCount - 1, array);
}
