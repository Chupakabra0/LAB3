#pragma once
#include "Interfaces.h"
#include <vector>
#include <GLFW/glfw3.h>

class Point : IMove, IColor, IDraw
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, Color color);
	//---------------------------------------------------------------------
	void ChangePosition(float dx, float dy) override;
	void ChangePosition(XY dxdy) override;
	//---------------------------------------------------------------------
	void SetPosition(float x, float y) override;
	void SetPosition(XY xy) override;
	//---------------------------------------------------------------------
	void PreviousPosition() override;
	//---------------------------------------------------------------------
	Color getColor() override;
	void setColor(Color color) override;
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
};