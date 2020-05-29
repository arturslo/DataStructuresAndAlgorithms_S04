using namespace std;

#include <iostream>
#include <string>

#include "RandomNumbers.h"
#include "Array.h"
#include "Sort.h"
#include "AnalyticsResponse.h"
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

	static void bubbleSort()
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
		int comparisonCount = Sort::bubbleSort(valueArray.get(), size);
		Array::print(valueArray.get(), size);
		cout << endl;

		AnalyticsResponse response = AnalyticsResponse(
			"bubbleSort",
			size,
			1,
			comparisonCount
		);

		cout << response.toString();
	}

	static void quickSort()
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
		int comparisonCount = Sort::quickSort(valueArray.get(), size);
		Array::print(valueArray.get(), size);
		cout << endl;

		AnalyticsResponse response = AnalyticsResponse(
			"quickSort",
			size,
			1,
			comparisonCount
		);

		cout << response.toString();
	}

	static void analytics()
	{
		AnalyticsRequest request1 = AnalyticsRequest("bubbleSort", Sort::bubbleSort);
		AnalyticsRequest request2 = AnalyticsRequest("quickSort", Sort::quickSort);
		vector<AnalyticsRequest> requestList = {  request1, request2 };
		vector<AnalyticsResponse> responseList = vector<AnalyticsResponse>();

		RandomNumbers::seedTime();

		for (AnalyticsRequest request : requestList)
		{
			for (int elementsToGenerate : request.getElementsToGenerateList())
			{
				for (int i = 1; i <= request.getRepetitionCount(); i++)
				{
					unique_ptr<int[]> valueArray;
					int size;

					tie(
						valueArray,
						size
					) = RandomNumbers::getUniqueIntArray(1, numeric_limits<int>::max(), elementsToGenerate);

					int comparisonCount = request.getAlgorithmFunction()(valueArray.get(), size);

					AnalyticsResponse response = AnalyticsResponse(
						request.getName(),
						size,
						i,
						comparisonCount
					);

					responseList.push_back(response);
				}
			}
		}
		
		//cout << AnalyticsResponse::listToJson(responseList) << endl;
		//return;

		for (AnalyticsResponse response : responseList)
		{
			cout << response.toString() << endl;
		}
	}
};

int main()
{
	string taskList = R"(Options:
1 - random integer array creation and output
2 - sort array 'bubble sort'
3 - sort array 'quick sort'
4 - analytics
5 - exit
)";

	const int RANDOM_INT_ARRAY = 1;
	const int BUBBLE_SORT = 2;
	const int QUICK_SORT = 3;
	const int ANALYTICS = 4;
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
		else if (choice == BUBBLE_SORT)
		{
			Tasks::bubbleSort();
		}
		else if (choice == QUICK_SORT)
		{
			Tasks::quickSort();
		}
		else if (choice == ANALYTICS)
		{
			Tasks::analytics();
		}

	} while (choice != EXIT);

	return 0;
}
