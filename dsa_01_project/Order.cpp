#include "Order.h"

void Order::bubbleSort(int* array, int elementCount)
{
	int* leftElement;
	int* rightElement;
	int temp;
	for (int ltrIndex = 1; ltrIndex < elementCount; ltrIndex++)
	{
		for (int rtlIndex = elementCount - 1; rtlIndex >= ltrIndex; rtlIndex--)
		{
			leftElement = &array[rtlIndex - 1];
			rightElement = &array[rtlIndex];

			if (*leftElement > * rightElement) {
				temp = *rightElement;
				*rightElement = *leftElement;
				*leftElement = temp;
			}
		}
	}
}
