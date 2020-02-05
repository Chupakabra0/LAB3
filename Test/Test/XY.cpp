#include "XY.h"

XY::XY() = default;
XY::XY(float x) : XY(x, x) {}
XY::XY(float x, float y) : x(x), y(y) {}

float XY::getX() const { return this->x; }

float XY::getY() const { return this->y; }

void XY::setX(float x) { this->x = x; }

void XY::setY(float y) { this->y = y; }

void XY::setXY(float x, float y) {
	this->setX(x);
	this->setY(y);
}

void XY::setXY(XY dxdy) { this->setXY(dxdy.getX(), dxdy.getY()); }

void XY::changeX(float dx) { this->x += dx; }

void XY::changeY(float dy) { this->y += dy; }

void XY::changeXY(float dx, float dy) {
	this->changeX(dx);
	this->changeY(dy);
}

void XY::changeXY(XY dxdy) { this->changeXY(dxdy.getX(), dxdy.getY()); }