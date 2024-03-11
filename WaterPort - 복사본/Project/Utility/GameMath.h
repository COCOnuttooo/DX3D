#pragma once

namespace GameMath
{
	float    Clamp(const float& value, float minValue, float maxValue);
	float Saturate(const float& value);

	Vector3 ClosestPointOnLine(const Vector3& start, const Vector3& end, const Vector3& point);

	float Random(const float& min, const float& max);
	int Random(const int& min, const int& max);
}