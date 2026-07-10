#include "Vec2.h"

#include <cmath>

Vec2::Vec2(float x, float y)
	: x(x)
	, y(y)
{
}
 
Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other)
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float value)
{
	return Vec2(x * value, y * value);
}


void Vec2::operator+=(const Vec2& other)
{
	x += other.x;
	y += other.y;
}

void Vec2::operator-=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;
}

void Vec2::operator*=(float value)
{
	x *= value;
	y *= value;
}


float Vec2::distance(const Vec2& destination) const
{
	return sqrtf(x * x + y * y);
}

