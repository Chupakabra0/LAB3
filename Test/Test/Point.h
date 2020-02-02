#pragma once
#include "Interfaces.h"

class Point : IMove, IColor
{
public:
	Point() = delete;
	Point(float x) : Point(x, x) {}
	Point(float x, float y) : Point(x, y, WHITE) {}
	Point(float x, float y, Color color) : x(x), y(y), IColor(color) {}
	virtual ~Point();
protected:
	float x;
	float y;
};

