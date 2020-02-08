#pragma once
#include "RGB.h"
#include "Angle.h"
#include "Scale.h"
#include "Dot.h"

class History {
public:
	History() = delete;
	explicit History(Dot dot, Scale scale, Angle angle, RGB color) : dot(dot), scale(scale), angle(angle), color(color) {}
	//---------------------------------------------------------------------
	Dot GetDot() const;
	Scale GetScale() const;
	Angle GetAngle() const;
	RGB GetColor() const;
protected:
	Dot dot;
	Scale scale;
	Angle angle;
	RGB color;
};