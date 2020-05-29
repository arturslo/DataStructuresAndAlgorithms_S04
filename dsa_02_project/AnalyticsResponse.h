#pragma once

using namespace std;

#include <string>
#include <vector>
#include "IStringable.h"

class AnalyticsResponse : IStringable
{
private:
	string name;
	int elementsInArray;
	int number;
	int comparisonCount;
public:
	AnalyticsResponse(
		string name,
		int elementsInArray,
		int number,
		int comparisonCount
	);
	string getName();
	int getElementsInArray();
	int getNumber();
	int getComparisonCount();
	string toString();
	static string listToJson(vector<AnalyticsResponse>& list);
};
