#include <utility>
#pragma once

class XY {
public:
	XY() = default;
	XY(float x);
	XY(float x, float y);
	//---------------------------------------------------------------------
	virtual float getX() const;
	virtual float getY() const;
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setXY(float x, float y);
	virtual void setXY(XY dxdy);
	//---------------------------------------------------------------------
	friend bool operator==(const XY& first, const XY& second) {
		return first.getX() == second.getX() && first.getY() == second.getY();
	}
	friend bool operator!=(const XY& first, const XY& second) {
		return !(first == second);
	}
	//---------------------------------------------------------------------
	virtual ~XY() = default;
protected:
	float x;
	float y;
};