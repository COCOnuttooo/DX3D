#include "Framework.h"
#include "GameMath.h"

float GameMath::Clamp(const float& value, float minValue, float maxValue)
{
    return min(minValue, min(maxValue, value));
}

float GameMath::Saturate(const float& value)
{
    return Clamp(value, 0.0f, 1.0f);
}
