#pragma once
#include "RGB.h"
#include "XY.h"
#include "Interfaces.h"

class History {
public:
	History() = delete;
	explicit History(XY dot, Scale scale, Angle angle, RGB color) : dot(dot), scale(scale), angle(angle), color(color) {}
	//---------------------------------------------------------------------
	XY GetDot() const;
	Scale GetScale() const;
	Angle GetAngle() const;
	RGB GetColor() const;
protected:
	XY dot;
	Scale scale;
	Angle angle;
	RGB color;
};
