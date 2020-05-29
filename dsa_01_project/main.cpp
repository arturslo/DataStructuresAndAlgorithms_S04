using namespace std;

#include <iostream>
#include <string>

#include "RandomNumbers.h"
#include "Array.h"
#include "SearchKey.h"
#include "Order.h"
#include "SearchAnalyticsResponse.h"
#include "AnalyticsRequest.h"

class Tasks
{
public:
	static void randomIntArray()
	{
		int elementsToGenerate;

		cout << "enter element count in array: ";
		cin >> elementsToGenerate;

		unique_ptr<int[]> valueArray;
		int size;

		RandomNumbers::seedTime();
		tie(
			valueArray,
			size
		) = RandomNumbers::getUniqueIntArray(1, numeric_limits<int>::max(), elementsToGenerate);

		cout << endl;
		Array::print(valueArray.get(), size);
	}

	static void searchInUnorderedArray()
	{
		int elementsToGenerate = 10;
		unique_ptr<int[]> valueArray;
		int size;

		RandomNumbers::seedTime();
		tie(
			valueArray,
			size
		) = RandomNumbers::getUniqueIntArray(1, numeric_limits<int>::max(), elementsToGenerate);

		Array::print(valueArray.get(), size);
		cout << endl;

		int key;
		cout << "input search key: ";
		cin >> key;

		int keyPosition;
		int comparisonCount;
		
		tie(
			keyPosition,
			comparisonCount
		) = SearchKey::linearWoBarrier(valueArray.get(), size, key);

		SearchAnalyticsResponse response = SearchAnalyticsResponse(
			"linearWoBarrier",
			size,
			1,
			key,
			keyPosition,
			comparisonCount
		);

		cout << endl;
		cout << response.toString();
	}

	static void searchInOrderedArray()
	{
		int elementsToGenerate = 10;
		unique_ptr<int[]> valueArray;
		int size;

		RandomNumbers::seedTime();
		tie(
			valueArray,
			size
		) = RandomNumbers::getUniqueIntArray(1, numeric_limits<int>::max(), elementsToGenerate);

		cout << "unordered array" << endl;
		Array::print(valueArray.get(), size);
		cout << endl;

		cout << "ordered array" << endl;
		Order::bubbleSort(valueArray.get(), size);
		Array::print(valueArray.get(), size);
		cout << endl;

		int key;
		cout << "input search key: ";
		cin >> key;

		int keyPosition;
		int comparisonCount;

		tie(
			keyPosition,
			comparisonCount
		) = SearchKey::approximationInOrderedArray(valueArray.get(), size, key);

		SearchAnalyticsResponse response = SearchAnalyticsResponse(
			"approximationInOrderedArray",
			size,
			1,
			key,
			keyPosition,
			comparisonCount
		);

		cout << endl;
		cout << response.toString();
	}

	static void searchAnalytics()
	{
		const string APPROXIMATION_FN_NAME = "approximationInOrderedArray";
		AnalyticsRequest request1 = AnalyticsRequest("linearWoBarrier", SearchKey::linearWoBarrier);
		AnalyticsRequest request2 = AnalyticsRequest(APPROXIMATION_FN_NAME, SearchKey::approximationInOrderedArray);
		vector<AnalyticsRequest> requestList = {  request1, request2 };
		vector<SearchAnalyticsResponse> responseList = vector<SearchAnalyticsResponse>();

		RandomNumbers::seedTime();

		for (AnalyticsRequest request : requestList)
		{
			for (int elementsToGenerate : request.getElementsToGenerateList())
			{
				int executionCount = request.getElementInArrayCount() + request.getElementNotInArrayCount();
				for (int i = 1; i <= executionCount; i++)
				{
					unique_ptr<int[]> valueArray;
					int size;

					tie(
						valueArray,
						size
					) = RandomNumbers::getUniqueIntArray(1, numeric_limits<int>::max(), elementsToGenerate);

					if (request.getName() == APPROXIMATION_FN_NAME) {
						Order::bubbleSort(valueArray.get(), size);
					}

					int key = 0;

					if (i <= request.getElementInArrayCount())
					{
						int arrayIndex = RandomNumbers::getInt(0, size - 1);
						key = valueArray[arrayIndex];
					}
					else
					{
						key -= i;
					}

					int keyPosition;
					int comparisonCount;

					tie(
						keyPosition,
						comparisonCount
					) = request.getAlgorithmFunction()(valueArray.get(), size, key);

					SearchAnalyticsResponse response = SearchAnalyticsResponse(
						request.getName(),
						size,
						i,
						key,
						keyPosition,
						comparisonCount
					);

					responseList.push_back(response);
				}
			}
		}
		
		//cout << SearchAnalyticsResponse::listToJson(responseList) << endl;
		//return;

		for (SearchAnalyticsResponse response : responseList)
		{
			cout << response.toString() << endl;
		}
	}
};

int main()
{
	string taskList = R"(Options:
1 - random integer array creation and output
2 - search key in unordered array 'secigas meklesanas metode (bez barjera)'
3 - order array and then search key 'aproksimacijas metode'
4 - search analytics
5 - exit
)";

	const int RANDOM_INT_ARRAY = 1;
	const int SEARCH_IN_UNORDERED_ARRAY = 2;
	const int SEARCH_IN_ORDERED_ARRAY = 3;
	const int SEARCH_ANALYTICS = 4;
	const int EXIT = 5;
	
	int choice;
	do
	{
		cout << endl;
		cout << taskList << endl;
		cout << "Enter choice: ";
		cin >> choice;
		cout << endl;

		if (choice == RANDOM_INT_ARRAY)
		{
			Tasks::randomIntArray();
		}
		else if (choice == SEARCH_IN_UNORDERED_ARRAY)
		{
			Tasks::searchInUnorderedArray();
		}
		else if (choice == SEARCH_IN_ORDERED_ARRAY)
		{
			Tasks::searchInOrderedArray();
		}
		else if (choice == SEARCH_ANALYTICS)
		{
			Tasks::searchAnalytics();
		}

	} while (choice != EXIT);

	return 0;
}
