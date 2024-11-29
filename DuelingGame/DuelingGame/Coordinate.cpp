
#include "Coordinate.h"
#include <algorithm>

bool Coordinate::operator==(const Coordinate& other) const
{
	return this->x == other.x && this->y == other.y;
}
bool Coordinate::operator<(const Coordinate& other) const
{
	return x < other.x || (x == other.x && y < other.y);
}
Coordinate Coordinate::operator-(const Coordinate& other) const
{
	return { x - other.x, y - other.y };
} 
Coordinate Coordinate::operator+(const Coordinate& other) const
{
	return { x + other.x, y + other.y };
} 
Coordinate Coordinate::operator*(const int& other) const
{
	return { x * other, y * other };
}

std::string Coordinate::ToString()
{
	return std::to_string(x) + ", " + std::to_string(y);
}

Coordinate Coordinate::Clamp()
{ 
	x = std::clamp(x, -1, 1); 
	y = std::clamp(y, -1, 1); 

	return Coordinate{ x, y };
}

Coordinate Coordinate::Magnitude(Coordinate& c1, Coordinate& c2)
{
	int yDiff = abs(c1.y - c2.y); 
	int xDiff = abs(c1.x - c2.x); 

	return { xDiff, yDiff };
} 

long Coordinate::Hash()
{
	long a = x >= 0 ? 2 * x : -2 * x - 1;
	long b = y >= 0 ? 2 * y : -2 * y - 1;
	long c = (a >= b ? a * a + a + b : a + b * b) / 2; 

	return x < 0 && y < 0 || x >= 0 && y >= 0 ? c : -c - 1; 
}

Coordinate Coordinate::ReverseHash(long hash)
{
	long c = hash >= 0 ? hash * 2 : -hash * 2 - 1;

	int a = 0;
	int b = 0;
	long z = floor(sqrt(c));
	if (z * (z + 1) <= c)
	{
		a = z;
		b = c - (z * z + z);
	}
	else
	{
		a = c - (z * z);
		b = z;
	}

	int x = (a % 2 == 0 ? a / 2 : -(a + 1) / 2);
	int y = (b % 2 == 0 ? b / 2 : -(b + 1) / 2);

	return { x, y };
}


