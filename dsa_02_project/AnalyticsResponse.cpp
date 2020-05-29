#include "AnalyticsResponse.h"
#include <sstream>

AnalyticsResponse::AnalyticsResponse(
	string name,
	int elementsInArray,
	int number,
	int comparisonCount
) {
	this->name = name;
	this->elementsInArray = elementsInArray;
	this->number = number;
	this->comparisonCount = comparisonCount;
}
string AnalyticsResponse::getName() { return this->name; }
int AnalyticsResponse::getElementsInArray() { return this->elementsInArray; }
int AnalyticsResponse::getNumber() { return this->number; }
int AnalyticsResponse::getComparisonCount() { return this->comparisonCount; }

string AnalyticsResponse::toString()
{
	ostringstream outputStream;

	outputStream << "name: " << this->name << endl;
	outputStream << "elements in array: " << this->elementsInArray << endl;
	outputStream << "number: " << this->number << endl;
	outputStream << "comparison count: " << this->comparisonCount << endl;

	return outputStream.str();
}

string AnalyticsResponse::listToJson(vector<AnalyticsResponse>& list)
{
	ostringstream outputStream;
	outputStream << "{analyticsResponseList:[";
	for (AnalyticsResponse& response : list)
	{
		outputStream << "{name:\"" << response.getName() << "\"";
		outputStream << ",elementsInArray:" << response.getElementsInArray();
		outputStream << ",number:" << response.getNumber();
		outputStream << ",comparisonCount:" << response.getComparisonCount() << "}";
		outputStream << ",";
	}
	outputStream << "]}";

	return outputStream.str();
}
