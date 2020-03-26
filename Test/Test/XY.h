#pragma once

class XY {
public:
	explicit XY();
	explicit XY(float x);
	explicit XY(float x, float y);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual float GetX() const;
	virtual void SetX(float x);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual float GetY() const;
	virtual void SetY(float y);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual void SetXY(float x, float y);
	virtual void SetXY(XY dxdy);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	friend bool operator==(const XY& first, const XY& second);
	friend bool operator!=(const XY& first, const XY& second);
	friend XY operator+=(XY& first, const XY& second);
	friend XY operator/=(XY& first, int second);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~XY() = default;
protected:
	float x;
	float y;
};