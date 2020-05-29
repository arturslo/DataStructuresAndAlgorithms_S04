#pragma once

using namespace std;

#include <iostream>

class Array
{
public:
	template<typename T>
	static void print(T*, int);
};

template<typename T>
void Array::print(T* array, int elementCount)
{
	for (int i = 0; i < elementCount; i++)
	{
		cout << array[i] << " ";
	}

	cout << endl;
}
