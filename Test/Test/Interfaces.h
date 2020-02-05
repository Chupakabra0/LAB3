#pragma once
#include <GLFW/glfw3.h>

class XY {
public:
	XY() = default;
	XY(float x) : XY(x, x) {}
	XY(float x, float y) : x(x), y(y) {}
	virtual float getX() const {
		return this->x;
	}
	virtual float getY() const {
		return this->y;
	}
	virtual void setX(float x) {
		this->x = x;
	}
	virtual void setY(float y) {
		this->y = y;
	}
	virtual void setXY(float x, float y) {
		this->setX(x);
		this->setY(y);
	}
	virtual void setXY(XY dxdy) {
		this->setXY(dxdy.getX(), dxdy.getY());
	}
	virtual void changeX(float dx) {
		this->x += dx;
	}
	virtual void changeY(float dy) {
		this->y += dy;
	}
	virtual void changeXY(float dx, float dy) {
		this->changeX(dx);
		this->changeY(dy);
	}
	virtual void changeXY(XY dxdy) {
		this->changeXY(dxdy.getX(), dxdy.getY());
	}
protected:
	float x;
	float y;
};

__interface IMove //интерфейс передвижения
{
	virtual void ChangePosition(float dx, float dy) abstract;
	virtual void SetPosition(float x, float y) abstract;
	virtual void ChangePosition(XY xy) abstract;
	virtual void SetPosition(XY xy) abstract;
	virtual void RememberPosition(float x, float y) abstract;
	virtual void RememberPosition(XY xy) abstract;
	virtual void PreviousPosition() abstract;
};

__interface  IDraw {
	virtual void Draw() abstract;
};

class RGB {
public:
	RGB() = default;
	RGB(float color) : RGB(color, color, color) {}
	RGB(float red, float green, float blue) : red(red), green(green), blue(blue) {}
	float getR() const {
		return this->red;
	}
	float getG() const {
		return this->green;
	}
	float getB() const {
		return this->blue;
	}
	void setR(float red) {
		this->red = red;
	}
	void setG(float green) {
		this->green = green;
	}
	void setB(float blue) {
		this->blue = blue;
	}
	void setRGB(float red, float green, float blue) {
		this->setR(red);
		this->setG(green);
		this->setB(blue);
	}
	virtual ~RGB() = default;
protected:
	float red;
	float green;
	float blue;
};