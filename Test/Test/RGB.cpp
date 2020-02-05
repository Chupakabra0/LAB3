#include "RGB.h"

RGB::RGB() = default;
RGB::RGB(float color) : RGB(color, color, color) {}
RGB::RGB(float red, float green, float blue) : red(red), green(green), blue(blue) {}

float RGB::getR() const { return this->red; }

float RGB::getG() const { return this->green; }

float RGB::getB() const { return this->blue; }

void RGB::setR(float red) { this->red = red; }

void RGB::setG(float green) { this->green = green; }

void RGB::setB(float blue) { this->blue = blue; }

void RGB::setRGB(float red, float green, float blue) {
	this->setR(red);
	this->setG(green);
	this->setB(blue);
}

RGB::~RGB() = default;