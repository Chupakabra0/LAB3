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

__interface IMove //��������� ������������
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