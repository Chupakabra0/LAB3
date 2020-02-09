#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 
#include "RGB.h"															 
#include "History.h"

class Point : public IMove, public IScale, public IDraw
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, RGB color);
	Point(XY xy, RGB color);
	XY GetXY() {
		return this->dot;
	}
	virtual ~Point();
protected:
	void Draw(sf::RenderWindow& window) override;
	//---------------------------------------------------------------------
	void SetPosition(XY xy) override;
	void ChangePosition(XY xy) override;
	//---------------------------------------------------------------------
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//---------------------------------------------------------------------
	void SetColor(RGB rgb) override;
	//---------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	//---------------------------------------------------------------------
	Scale scale;
	XY dot;
	RGB color;
	std::vector<History> history;
};
