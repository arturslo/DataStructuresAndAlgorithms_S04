using namespace std;

#include "HashTable.h"
#include "Float.h"
#include <sstream>

const float HashTable::DEFAULT_LOAD_THRESHOLD = 0.8f;

void HashTable::fillWithNullElements(int* array)
{
	for (int i = 0; i < this->capacity; i++)
	{
		array[i] = NULL_ELEMENT;
	}
}

int HashTable::hash(int key)
{
	return abs(key % this->capacity);

}

int HashTable::linearFn(int collisionResolutionTries)
{
	const static int CONST_C = 1;

	return CONST_C * collisionResolutionTries;
}

int HashTable::getAddress(int key, int collisionResolutionTries)
{
	int address = this->hash(key) + this->linearFn(collisionResolutionTries);

	return address % this->capacity;
}

void HashTable::setKey(int address, int key)
{
	this->keyArray[address] = key;
}

int HashTable::getKey(int address)
{
	return this->keyArray[address];
}

void HashTable::setValue(int address, int value)
{
	this->valueArray[address] = value;
}

int HashTable::getValue(int address)
{
	return this->valueArray[address];
}

bool HashTable::isNull(int keyValue)
{
	return keyValue == NULL_ELEMENT;
}

bool HashTable::isTombstone(int keyValue)
{
	return keyValue == TOMBSTONE_ELEMENT;
}

bool HashTable::isNullOrTombstone(int keyValue)
{
	return isNull(keyValue) || isTombstone(keyValue);
}

bool HashTable::canResize()
{
	if (Float::lge(this->getLoadFactor(), this->getLoadThreshold())) {
		return true;
	}

	return false;
}

void HashTable::resize()
{
	int* oldKeyArray = this->keyArray;
	int* oldValueArray = this->valueArray;

	int oldCapacity = this->capacity;
	int newCapacity = oldCapacity * 2;

	int* keyArray = new int[newCapacity];
	int* valueArray = new int[newCapacity];

	this->capacity = newCapacity;
	this->elementCount = 0;
	this->totalElementCount = 0;

	this->keyArray = keyArray;
	this->valueArray = valueArray;

	this->fillWithNullElements(this->keyArray);

	for (int i = 0; i < oldCapacity; i++)
	{
		int key = oldKeyArray[i];
		if (this->isNullOrTombstone(key)) {
			continue;
		}
		int value = oldValueArray[i];

		this->insert(key, value);
	}

	delete[] oldKeyArray;
	delete[] oldValueArray;
}

HashTable::HashTable() : HashTable(DEFAULT_CAPACITY) {};

HashTable::HashTable(int capacity, float loadThreshold)
{
	this->capacity = capacity;
	this->elementCount = 0;
	this->totalElementCount = 0;
	this->loadThreshold = loadThreshold;
	this->keyArray = new int[this->capacity];
	this->valueArray = new int[this->capacity];

	this->fillWithNullElements(this->keyArray);
}

HashTable::~HashTable()
{
	delete[] this->keyArray;
	delete[] this->valueArray;
}

float HashTable::getLoadFactor()
{
	return (float)this->totalElementCount / (float)this->capacity;
}

float HashTable::getLoadThreshold()
{
	return this->loadThreshold;
}

int HashTable::getElementCount()
{
	return this->elementCount;
}

int HashTable::getTotalElementCount()
{
	return this->totalElementCount;
}

void HashTable::insert(int key, int value)
{
	if (this->isNullOrTombstone(key)) {
		return;
	}

	if (this->canResize()) {
		this->resize();
	}

	int tries = 0;

	do
	{
		int address = this->getAddress(key, tries);
		int keyValue = this->getKey(address);

		if (this->isNull(keyValue)) {
			this->setKey(address, key);
			this->setValue(address, value);
			this->elementCount++;
			this->totalElementCount++;
			break;
		}

		if (key == keyValue) {
			this->setValue(address, value);
			break;
		}

		tries++;
	} while (tries != this->capacity);
}

int HashTable::get(int key)
{
	int returnValue = NULL_ELEMENT;

	if (this->isNullOrTombstone(key)) {
		return returnValue;
	}

	int tries = 0;

	do
	{
		int address = this->getAddress(key, tries);
		int keyValue = this->getKey(address);

		if (this->isNull(keyValue)) {
			break;
		}

		if (key == keyValue) {
			returnValue = this->getValue(address);
			break;
		}

		tries++;
	} while (tries != this->capacity);

	return returnValue;
}

void HashTable::remove(int key)
{
	if (this->isNullOrTombstone(key)) {
		return;
	}

	int tries = 0;

	do
	{
		int address = this->getAddress(key, tries);
		int keyValue = this->getKey(address);

		if (this->isNull(keyValue)) {
			break;
		}

		if (key == keyValue) {
			this->setKey(address, TOMBSTONE_ELEMENT);
			this->elementCount--;
			break;
		}

		tries++;
	} while (tries != this->capacity);
}

string HashTable::toString()
{
	ostringstream outputStream;
	for (int i = 0; i < this->capacity; i++)
	{
		int key = this->getKey(i);
		string keyText = to_string(key);
		if (this->isNull(key)) { keyText = "N"; }
		if (this->isTombstone(key)) { keyText = "T"; }
		outputStream << "{" << keyText << "," << this->getValue(i) << "}";
	}

	return outputStream.str();
}

tuple<unique_ptr<int[]>, int> HashTable::copyValueArray()
{
	int copyArrayCapacity = this->getElementCount();
	unique_ptr<int[]> copyValueArray =  make_unique<int[]>(copyArrayCapacity);
	int copyArrayIndex = 0;

	for (int i = 0; i < this->capacity; i++)
	{
		int key = this->getKey(i);
		if (this->isNullOrTombstone(key)) {
			continue;
		}

		if (copyArrayIndex >= copyArrayCapacity) {
			continue;
		}

		copyValueArray[copyArrayIndex] = this->getValue(i);
		++copyArrayIndex;
	}

	return make_tuple(move(copyValueArray), copyArrayCapacity);
}
