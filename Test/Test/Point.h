#pragma once
#include "Interfaces.h"
#include <vector>
#include "RGB.h"

class Point : public IMove, public IDraw, public IRotate, public IScale //TODO ğåàëèçîâàòü èíòåğôåéñ ìàñøòàáà
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
	void SetPosition(float x, float y) override;
	void SetPosition(XY xy) override;
	void PreviousPosition() override;
	XY GetPosition() const;
	//---------------------------------------------------------------------
	void ChangeAngle(float angle) override;
	void SetAngle(float angle) override;
	void PreviousAngle() override;
	float getAngle() const;
	//---------------------------------------------------------------------
	void Draw() override {}
	//---------------------------------------------------------------------
	RGB GetColor() const;
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void RememberPosition(XY xy) override;
	void RememberPosition(float x, float y) override;
	void RememberAngle(float angle) override;
	//---------------------------------------------------------------------
	XY coordinate;
	float angle;
	std::vector<XY> historyPosition; //TODO ĞÅÀËÈÇÎÂÀÒÜ ÊËÀÑÑ-ÊÎÌÏÎÇÈÖÈŞ ÊËÀÑÑÎÂ ÒÎ×ÊÈ, ÓÃËÀ, ÌÀÑØÒÀÁÀ È ÖÂÅÒÀ ÄËß ÂÅÄÅÍÈß ÈÑÒÎĞÈÈ ÈÇÌÅÍÅÍÈÉ
	std::vector<float> historyAngel;
	RGB color;
};