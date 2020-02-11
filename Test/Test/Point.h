#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 
#include "RGB.h"															 
#include "History.h"

struct Figure : IMove, IScale, IDraw, IRotate {
	Figure() = default;
	virtual ~Figure() = default;
};

class Point : public Figure
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, RGB color);
	Point(XY xy, RGB color);
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
	void SetAngle(Angle angle) override {
		this->angle = angle;
	}
	void ChangeAngle(Angle angle) override {
		this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
	}
	//---------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	//---------------------------------------------------------------------
	Scale scale;
	Angle angle;
	XY dot;
	RGB color;
	std::vector<History> history;
};
