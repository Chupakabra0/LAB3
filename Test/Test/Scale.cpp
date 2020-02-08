#include "Scale.h"

void Scale::SetScale(float percent)
{
	this->scale = percent;
}

float Scale::GetScale() const {
	return this->scale;
}

bool operator==(const Scale& first, const Scale& second) { return first.GetScale() == second.GetScale(); }

bool operator!=(const Scale& first, const Scale& second) { return !(first == second); }