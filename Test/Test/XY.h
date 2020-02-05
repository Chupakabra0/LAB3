#pragma once

class XY {
public:
	XY();
	XY(float x);
	XY(float x, float y);

	virtual float getX() const;

	virtual float getY() const;

	virtual void setX(float x);

	virtual void setY(float y);

	virtual void setXY(float x, float y);

	virtual void setXY(XY dxdy);

	virtual void changeX(float dx);

	virtual void changeY(float dy);

	virtual void changeXY(float dx, float dy);

	virtual void changeXY(XY dxdy);
protected:
	float x{};
	float y{};
};