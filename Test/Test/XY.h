#pragma once

class XY {
public:
	XY();
	explicit XY(float x);
	explicit XY(float x, float y);
	//---------------------------------------------------------------------
	virtual float getX() const;
	virtual float getY() const;
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setXY(float x, float y);
	virtual void setXY(XY dxdy);
	//---------------------------------------------------------------------
	friend bool operator==(const XY& first, const XY& second);
	friend bool operator!=(const XY& first, const XY& second);
	friend XY operator+=(const XY& first, const XY& second) {
		return XY(first.getX() + second.getX(), first.getY() + second.getY());
	}
	friend XY operator /=(const XY& first, int second) {
		return XY(first.getX() / second, first.getY() / second);
	}
	//---------------------------------------------------------------------
	virtual ~XY() = default;
protected:
	float x;
	float y;
};