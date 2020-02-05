#pragma once
#include "Interfaces.h"
#include <vector>
#include "RGB.h"

class Point : public IMove, public IDraw
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, float color);
	Point(float x, float y, float red, float green, float blue);
	Point(float x, float y, RGB color);
	//---------------------------------------------------------------------
	void ChangePosition(float dx, float dy) override;
	void ChangePosition(XY dxdy) override;
	//---------------------------------------------------------------------
	void SetPosition(float x, float y) override;
	void SetPosition(XY xy) override;
	//---------------------------------------------------------------------
	void PreviousPosition() override;
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	XY getPosition() const;
	//---------------------------------------------------------------------
	void Draw() override {
	}
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void RememberPosition(XY xy) override;
	void RememberPosition(float x, float y) override;
	//---------------------------------------------------------------------
	XY coordinate;
	std::vector<XY> history;
	RGB color;
};
