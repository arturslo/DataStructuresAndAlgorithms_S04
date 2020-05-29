#pragma once

using namespace std;

#include <iostream>
#include <tuple>
#include <memory>
#include "IStringable.h"

class HashTable : IStringable
{
private:
	int capacity;
	int totalElementCount;
	int elementCount;
	float loadThreshold;
	int* keyArray;
	int* valueArray;

	void fillWithNullElements(int* array);
	int hash(int key);
	int linearFn(int collisionResolutionTries);
	int getAddress(int key, int collisionResolutionTries);
	void setKey(int address, int key);
	int getKey(int address);
	void setValue(int address, int value);
	int getValue(int address);
	bool isNull(int keyValue);
	bool isTombstone(int keyValue);
	bool isNullOrTombstone(int keyValue);
	bool canResize();
	void resize();

public:
	const static int NULL_ELEMENT = numeric_limits<int>::min();
	const static int TOMBSTONE_ELEMENT = numeric_limits<int>::min() + 1;
	const static int DEFAULT_CAPACITY = 10;
	const static float DEFAULT_LOAD_THRESHOLD;

	HashTable();
	HashTable(int capacity, float loadThreshold = DEFAULT_LOAD_THRESHOLD);
	~HashTable();

	float getLoadFactor();
	float getLoadThreshold();
	int getElementCount();
	int getTotalElementCount();
	void insert(int key, int value);
	int get(int key);
	void remove(int key);
	string toString();
	tuple<unique_ptr<int[]>, int> copyValueArray();
};
