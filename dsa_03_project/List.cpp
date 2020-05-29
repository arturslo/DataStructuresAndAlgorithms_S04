using namespace std;

#include <iostream>

class ListBlock
{
public:
	ListBlock* left;
	ListBlock* right;
	int value;

	ListBlock(int value)
	{
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class List
{
private:
	void addFirstBlock(ListBlock* newBlock)
	{
		this->firstBlock = newBlock;
		this->lastBlock = newBlock;
	}
public:
	const int INDEX_NOT_FOUND = -1;

	ListBlock* firstBlock;
	ListBlock* lastBlock;
	
	List()
	{
		this->firstBlock = nullptr;
		this->lastBlock = nullptr;
	}

	friend ostream& operator<<(ostream& os, List& list) {
		if (list.isEmpty())
		{
			os << "[]";
		}

		os << "[";

		ListBlock* block = list.firstBlock;
		while (block != nullptr)
		{
			os << "{" << block->left << "," << block->value << "," << block->right << "}";
			os << ",";

			block = block->right;
		}

		os << "]";

		return os;
	}

	void print()
	{
		ListBlock* block = this->firstBlock;
		while (block != nullptr)
		{
			cout << block->value << " ";

			block = block->right;
		}
	}

	void reversePrint()
	{
		ListBlock* block = this->lastBlock;
		while (block != nullptr)
		{
			cout << block->value << " ";

			block = block->left;
		}
	}

	bool isEmpty()
	{
		if (this->firstBlock == nullptr && this->lastBlock == nullptr)
		{
			return true;
		}

		return false;
	}

	void append(int value)
	{
		auto newBlock = new ListBlock(value);

		if (this->isEmpty())
		{
			this->addFirstBlock(newBlock);

			return;
		}

		this->lastBlock->right = newBlock;
		newBlock->left = lastBlock;
		this->lastBlock = newBlock;
	}

	void prepend(int value)
	{
		auto newBlock = new ListBlock(value);

		if (this->isEmpty())
		{
			this->addFirstBlock(newBlock);

			return;
		}

		this->firstBlock->left = newBlock;
		newBlock->right = firstBlock;
		this->firstBlock = newBlock;
	}

	int find(int key, int startIndex = 0)
	{
		int foundAtIndex = INDEX_NOT_FOUND;
		ListBlock* block = this->firstBlock;
		int index = 0;

		while (block != nullptr)
		{
			if (index >= startIndex && block->value == key)
			{
				foundAtIndex = index;
				break;
			}

			block = block->right;
			index++;
		}

		return foundAtIndex;
	}

	void insertAfter(int key, int value)
	{
		bool hasInserted = false;
		ListBlock* block = this->firstBlock;

		while (block != nullptr)
		{
			if (block->value == key)
			{
				if (block->right == nullptr)
				{
					this->append(value);
				}
				else
				{
					auto newBlock = new ListBlock(value);
					newBlock->left = block;
					newBlock->right = block->right;

					block->right->left = newBlock;
					block->right = newBlock;
				}

				hasInserted = true;
				block = block->right;
			}

			block = block->right;
		}

		if (!hasInserted)
		{
			this->prepend(value);
		}
	}

	float average()
	{
		int elementCount = 0;
		int sum = 0;
		ListBlock* block = this->firstBlock;
		while (block != nullptr)
		{
			elementCount++;
			sum += block->value;

			block = block->right;
		}

		if (elementCount == 0)
		{
			return 0;
		}

		return (float)sum / (float)elementCount;
	}
};
