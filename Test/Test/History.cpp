#include "History.h"


History::History(XY dot, Scale scale, Angle angle, sf::Color color): dot(dot), scale(std::move(scale)), angle(angle), color(color) {}

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