#include "Point.h"
Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, 0.f) {}
Point::Point(float x, float y, float color) : Point(x, y, RGB(color)) {}
Point::Point(float x, float y, float red, float green, float blue) : Point(x, y, RGB(red, green, blue)) {}

Point::Point(float x, float y, RGB color) : coordinate(x, y), color(color) {
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
