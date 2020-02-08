#include "RGB.h"

RGB::RGB() = default;
RGB::RGB(float color) : RGB(color, color, color) {}
RGB::RGB(float red, float green, float blue) : red(red), green(green), blue(blue) {}

float RGB::getR() const {
	return this->red;
}

float RGB::getG() const {
	return this->green;
}

float RGB::getB() const {
	return this->blue;
}

void RGB::setR(float red) {
	this->red = red;
}

void RGB::setG(float green) {
	this->green = green;
}

void RGB::setB(float blue) {
	this->blue = blue;
}

void RGB::setRGB(float red, float green, float blue) {
	this->setR(red);
	this->setG(green);
	this->setB(blue);
}

RGB::~RGB() = default;

bool operator==(const RGB& first, const RGB& second) {
	return first.getB() == second.getB() && first.getG() == second.getG() && first.getR() == second.getR();
}

bool operator!=(const RGB& first, const RGB& second) {
	return !(first == second);
}

RGB& RGB::operator=(RGB& rgb) {
	if (this->getR() != rgb.getR()) this->setR(rgb.getR());
	if (this->getG() != rgb.getG()) this->setG(rgb.getG());
	if (this->getB() != rgb.getB()) this->setB(rgb.getB());
	return *this;
}
