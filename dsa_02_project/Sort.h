#pragma once

using namespace std;

class Sort
{
protected:
	static int innerQuickSort(int left, int right, int* array);
public:
	static int bubbleSort(int* array, int elementCount);
	static int quickSort(int* array, int elementCount);
};
