#pragma once

using namespace std;

#include<string>
#include<vector>
#include<functional>

typedef function<int(int* array, int elementCount)> AlgorithmFunction;

class AnalyticsRequest
{
private:
	string name;
	vector<int> elementsToGenerateList;
	int repetitionCount;
	AlgorithmFunction algorithmFunction;
public:
	AnalyticsRequest(string name, AlgorithmFunction algorithmFunction);

	string getName();
	vector<int> getElementsToGenerateList();
	int getRepetitionCount();
	AlgorithmFunction getAlgorithmFunction();
};
