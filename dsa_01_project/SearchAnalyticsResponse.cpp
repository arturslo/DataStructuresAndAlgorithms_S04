#include "SearchAnalyticsResponse.h"
#include "SearchKey.h"
#include <sstream>

SearchAnalyticsResponse::SearchAnalyticsResponse(
	string name,
	int elementsInArray,
	int number,
	int searchKey,
	int keyPosition,
	int comparisonCount
) {
	this->name = name;
	this->elementsInArray = elementsInArray;
	this->number = number;
	this->searchKey = searchKey;
	this->keyPosition = keyPosition;
	this->comparisonCount = comparisonCount;
}
string SearchAnalyticsResponse::getName() { return this->name; }
int SearchAnalyticsResponse::getElementsInArray() { return this->elementsInArray; }
int SearchAnalyticsResponse::getNumber() { return this->number; }
int SearchAnalyticsResponse::getSearchKey() { return this->searchKey; }
int SearchAnalyticsResponse::getKeyPosition() { return this->keyPosition; }
int SearchAnalyticsResponse::getComparisonCount() { return this->comparisonCount; }

string SearchAnalyticsResponse::toString()
{
	ostringstream outputStream;

	outputStream << "name: " << this->name << endl;
	outputStream << "elements in array: " << this->elementsInArray << endl;
	outputStream << "number: " << this->number << endl;
	outputStream << "search key: " << this->searchKey << endl;

	string keyText = "key not found";
	if (this->keyPosition != SearchKey::POSITION_NOT_FOUND) {
		keyText = "key found at position: " + to_string(this->keyPosition);
	}

	outputStream << keyText << endl;
	outputStream << "comparison count: " << this->comparisonCount << endl;

	return outputStream.str();
}

string SearchAnalyticsResponse::listToJson(vector<SearchAnalyticsResponse>& list)
{
	ostringstream outputStream;
	outputStream << "{searchAnalyticsResponseList:[";
	for (SearchAnalyticsResponse& response : list)
	{
		outputStream << "{name:\"" << response.getName() << "\"";
		outputStream << ",elementsInArray:" << response.getElementsInArray();
		outputStream << ",number:" << response.getNumber();
		outputStream << ",searchKey:" << response.getSearchKey();
		outputStream << ",keyPosition:" << response.getKeyPosition();
		outputStream << ",comparisonCount:" << response.getComparisonCount() << "}";
		outputStream << ",";
	}
	outputStream << "]}";

	return outputStream.str();
}
