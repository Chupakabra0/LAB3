#include "Point.h"
Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, WHITE) {}

Point::Point(float x, float y, Color color): coordinate(x, y), IColor(color) {
	this->Point::RememberPosition(this->coordinate);
}

void Point::ChangePosition(float dx, float dy) {
	this->coordinate.changeXY(dx, dy);
	this->RememberPosition(this->coordinate);
}

void Point::ChangePosition(XY dxdy) {
	this->coordinate.changeXY(dxdy);
	this->RememberPosition(this->coordinate);
}

void Point::SetPosition(float x, float y) {
	this->coordinate.setXY(x, y);
	this->RememberPosition(this->coordinate);
}

void Point::SetPosition(XY xy) {
	this->coordinate.setXY(xy);
	this->RememberPosition(this->coordinate);
}

void Point::PreviousPosition() {
	if (!this->history.empty()) {
		this->history.pop_back();
		this->SetPosition(this->history[this->history.size() - 1]);
	}
}

Color Point::getColor() {
	return this->color;
}

void Point::setColor(Color color) {
	this->color = color;
}

XY Point::getPosition() const {
	return this->coordinate;
}

Point::~Point() = default;

void Point::RememberPosition(XY xy) {
	this->history.push_back(xy);
}

void Point::RememberPosition(float x, float y) {
	const XY temp(x, y);
	this->history.push_back(temp);
}
