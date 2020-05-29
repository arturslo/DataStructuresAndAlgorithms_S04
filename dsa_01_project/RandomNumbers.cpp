using namespace std;

#include "RandomNumbers.h"
#include "HashTable.h"
#include "Float.h"
#include <ctime>

void RandomNumbers::seedTime()
{
	srand(time(NULL));
}

/*
rangeEnd is limited by RAND_MAX 32767
should use c++11 <random>
*/
int RandomNumbers::getInt(int rangeStart, int rangeEnd)
{
	int random = rangeStart + rand() % (rangeEnd - rangeStart + 1);

	return random;
}

tuple<unique_ptr<int[]>, int> RandomNumbers::getUniqueIntArray(int rangeStart, int rangeEnd, int elementCount)
{
	float percentToAdd = Float::round(1 - HashTable::DEFAULT_LOAD_THRESHOLD, 2);
	int elementsToAdd = elementCount * percentToAdd;
	int hashTableCapacity = elementCount + elementsToAdd;
	HashTable hashTable = HashTable(hashTableCapacity);

	while (hashTable.getElementCount() != elementCount)
	{
		int randInt = getInt(rangeStart, rangeEnd);
		hashTable.insert(randInt, randInt);
	}

	return hashTable.copyValueArray();
}

float RandomNumbers::getFloat(float min, float max)
{
	float range = max - min;
	float random = (float)rand() / (float)RAND_MAX;
	float fresult = (random * range) + min;

	return fresult;
}
