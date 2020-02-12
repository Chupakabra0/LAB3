#include "History.h"

XY History::GetDot() const {
	return this->dot;
}

Scale History::GetScale() const {
	return this->scale;
}

Angle History::GetAngle() const {
	return this->angle;
}

sf::Color History::GetColor() const {
	return this->color;
}