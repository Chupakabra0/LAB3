#include "History.h"

XY History::GetDot() const {
	return this->dot;
}

float History::GetScale() const {
	return this->scale;
}

float History::GetAngle() const {
	return this->angle;
}

RGB History::GetColor() const {
	return this->color;
}
