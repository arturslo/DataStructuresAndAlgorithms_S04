#pragma once

#include <cmath>

class Float
{
public:
	const static float DEFAULT_EPSILON;
	static bool eq(float left, float right, float epsilon = DEFAULT_EPSILON);
	static bool lg(float left, float right, float epsilon = DEFAULT_EPSILON);
	static bool lge(float left, float right, float epsilon = DEFAULT_EPSILON);
	static float round(float value, int decimalPlaces);
};
