#pragma once

using namespace std;

#include <string>

class IStringable
{
public:
	virtual string toString() = 0;
};
