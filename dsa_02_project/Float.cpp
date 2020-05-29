#include "Float.h"
#include <cmath>

const float Float::DEFAULT_EPSILON = 0.01f;

bool Float::eq(float left, float right, float epsilon)
{
	if (fabs(left - right) < epsilon) {
		return true;
	}

	return false;
}

bool Float::lg(float left, float right, float epsilon)
{
	if (eq(left, right, epsilon)) {
		return false;
	}

	if (left < right) {
		return false;
	}

	return true;
}

bool Float::lge(float left, float right, float epsilon)
{
	return eq(left, right, epsilon) || lg(left, right, epsilon);
}

float Float::round(float value, int decimalPlaces)
{
	float multiplier = pow(10.0, decimalPlaces);

	return std::round(value * multiplier) / multiplier;
}