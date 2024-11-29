#pragma once
#include <string>

struct Coordinate
{
	int x;
	int y;

	bool operator==(const Coordinate& other) const;
	bool operator<(const Coordinate& other) const;
	Coordinate operator-(const Coordinate& other) const;
	Coordinate operator+(const Coordinate& other) const;
	Coordinate operator*(const int& other) const;
	std::string ToString();
	Coordinate Clamp(); 
	long Hash();
	static Coordinate ReverseHash(long hash);
	static Coordinate Magnitude(Coordinate& c1, Coordinate& c2);
};
 

