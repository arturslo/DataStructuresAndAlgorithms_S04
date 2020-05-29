#pragma once

using namespace std;

#include <string>
#include <vector>
#include "IStringable.h"

class SearchAnalyticsResponse : IStringable
{
private:
	string name;
	int elementsInArray;
	int number;
	int searchKey;
	int keyPosition;
	int comparisonCount;
public:
	SearchAnalyticsResponse(
		string name,
		int elementsInArray,
		int number,
		int searchKey,
		int keyPosition,
		int comparisonCount
	);
	string getName();
	int getElementsInArray();
	int getNumber();
	int getSearchKey();
	int getKeyPosition();
	int getComparisonCount();
	string toString();
	static string listToJson(vector<SearchAnalyticsResponse>& list);
};
