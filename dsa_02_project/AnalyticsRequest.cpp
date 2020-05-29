#include "AnalyticsRequest.h"

AnalyticsRequest::AnalyticsRequest(string name, AlgorithmFunction algorithmFunction)
{
	this->name = name;
	this->algorithmFunction = algorithmFunction;
	this->repetitionCount = 10;
	this->elementsToGenerateList = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
}

string AnalyticsRequest::getName() { return this->name; }
vector<int> AnalyticsRequest::getElementsToGenerateList() { return this->elementsToGenerateList; }
int AnalyticsRequest::getRepetitionCount() { return this->repetitionCount; }
AlgorithmFunction AnalyticsRequest::getAlgorithmFunction() { return this->algorithmFunction; }
