using namespace std;

#include <iomanip>
#include "List.cpp"

int main()
{
	
	auto list = List();
	list.append(1);
	list.append(7);
	list.append(3);
	list.append(7);
	list.append(2);
	list.append(4);
	list.append(3);
	list.append(1);
	list.append(13);
	list.append(0);

	// inner
	cout << "list inner representation" << endl;
	cout << list << endl;

	cout << endl;

	// iterate
	cout << "list values:" << endl;
	list.print();
	cout << endl;
	cout << "list value reversed:" << endl;
	list.reversePrint();
	cout << endl;

	cout << endl;

	// find key
	cout << "find: 7 start index: 0 found at index: " << list.find(7) << endl;
	cout << "find: 7 start index: 0 found at index: " << list.find(7, 0) << endl;
	cout << "find: 7 start index: 3 found at index: " << list.find(7, 3) << endl;
	cout << "find (non-existent): 8 start index: 0 found at index: " << list.find(8) << endl;

	cout << endl;

	// insert after
	cout << "after key: 7 insert: 7" << endl;
	list.insertAfter(7, 7);

	cout << "list values:" << endl;
	list.print();
	cout << endl;

	cout << "after key (non-existent): 9 insert: 11" << endl;
	list.insertAfter(9, 11);

	cout << "list values:" << endl;
	list.print();
	cout << endl;

	cout << endl;

	// average
	cout << "average: " << list.average() << endl;

	return 0;
}
