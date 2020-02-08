#include "Dot.h"

void Dot::SetPosition(float x, float y) {
	this->dot.setXY(x, y);
}

void Dot::SetPosition(XY xy) {
	this->dot.setXY(xy);
}

XY Dot::GetPosition() const {
	return this->dot;
}

bool operator==(const Dot& first, const Dot& second) { return first.GetPosition() == second.GetPosition(); }

bool operator!=(const Dot& first, const Dot& second) { return !(first == second); }