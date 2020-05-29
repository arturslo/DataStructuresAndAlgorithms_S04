#pragma once

using namespace std;

#include<string>
#include<vector>
#include<functional>

typedef function<tuple<int, int>(int* array, int elementCount, int key)> AlgorithmFunction;

class AnalyticsRequest
{
private:
	string name;
	vector<int> elementsToGenerateList;
	int elementInArrayCount;
	int elementNotInArrayCount;
	AlgorithmFunction algorithmFunction;
public:
	AnalyticsRequest(string name, AlgorithmFunction algorithmFunction);

	string getName();
	vector<int> getElementsToGenerateList();
	int getElementInArrayCount();
	int getElementNotInArrayCount();
	AlgorithmFunction getAlgorithmFunction();
};
