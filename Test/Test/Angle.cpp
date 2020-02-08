#include "Angle.h"

void Angle::SetAngle(float angle) {
	this->angle = angle;
}

float Angle::GetAngle() const {
	return this->angle;
}

bool operator==(const Angle& first, const Angle& second) { return first.GetAngle() == second.GetAngle(); }

bool operator!=(const Angle& first, const Angle& second) { return !(first == second); }