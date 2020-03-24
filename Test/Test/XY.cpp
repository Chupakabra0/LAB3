#include "XY.h"

XY::XY() : XY(0) {}
XY::XY(float x) : XY(x, x) {}
XY::XY(float x, float y) : x(x), y(y) {}

float XY::getX() const {
	return this->x;
}

float XY::getY() const {
	return this->y;
}

void XY::setX(float x) {
	this->x = x;
}

void XY::setY(float y) {
	this->y = y;
}

void XY::setXY(float x, float y) {
	this->setX(x);
	this->setY(y);
}

void XY::setXY(XY dxdy) {
	this->setXY(dxdy.getX(), dxdy.getY());
}

bool operator==(const XY& first, const XY& second) {
	return (first.getX() == second.getX()) && (first.getY() == second.getY());
}

bool operator!=(const XY& first, const XY& second) {
	return !(first == second);
}

XY operator+=(XY& first, const XY& second) {
	first = XY(first.getX() + second.getX(), first.getY() + second.getY());
	return first;
}

XY operator/=(XY& first, int second) {
	first = XY(first.getX() / static_cast<float>(second), first.getY() / static_cast<float>(second));
	return first;
}