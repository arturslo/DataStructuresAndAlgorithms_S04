#include "AnalyticsRequest.h"

AnalyticsRequest::AnalyticsRequest(string name, AlgorithmFunction algorithmFunction)
{
	this->name = name;
	this->algorithmFunction = algorithmFunction;

	this->elementInArrayCount = 10;
	this->elementNotInArrayCount = 10;
	this->elementsToGenerateList = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
}

string AnalyticsRequest::getName() { return this->name; }
vector<int> AnalyticsRequest::getElementsToGenerateList() { return this->elementsToGenerateList; }
int AnalyticsRequest::getElementInArrayCount() { return this->elementInArrayCount; }
int AnalyticsRequest::getElementNotInArrayCount() { return this->elementNotInArrayCount; }
AlgorithmFunction AnalyticsRequest::getAlgorithmFunction() { return this->algorithmFunction; }
