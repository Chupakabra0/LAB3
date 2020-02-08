#pragma once
#include "RGB.h"
#include "XY.h"

class History {
public:
	History() = delete;
	explicit History(XY dot, float scale, float angle, RGB color) : dot(dot), scale(scale), angle(angle), color(color) {}
	//---------------------------------------------------------------------
	XY GetDot() const;
	float GetScale() const;
	float GetAngle() const;
	RGB GetColor() const;
protected:
	XY dot;
	float scale;
	float angle;
	RGB color;
};