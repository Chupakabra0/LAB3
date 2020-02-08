#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 
#include "RGB.h"															 
#include "History.h"

class Point : public IMove, public IScale, public IDraw, public IColor, public IHistory
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, RGB color);
	Point(XY xy, RGB color);
	//---------------------------------------------------------------------
	void Draw(sf::RenderWindow& window) override;
	//---------------------------------------------------------------------
	void SetPosition(float xy) override;
	void SetPosition(float x, float y) override;
	void SetPosition(XY xy) override;
	void ChangePosition(float xy) override;
	void ChangePosition(float x, float y) override;
	void ChangePosition(XY xy) override;
	//---------------------------------------------------------------------
	void SetScale(float scale) override;
	void ChangeScale(float scale) override;
	//---------------------------------------------------------------------
	void SetColor(float red, float green, float blue) override;
	void SetColor(RGB rgb) override;
	//---------------------------------------------------------------------
	void PreviousCondition() override;
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void AdminSetPosition(XY xy);
	void AdminChangePosition(XY xy);
	//---------------------------------------------------------------------
	void AdminSetScale(float scale);
	void AdminChangeScale(float scale);
	//---------------------------------------------------------------------
	void AdminSetColor(RGB rgb);
	//---------------------------------------------------------------------
	void RememberCondition() override;
	//---------------------------------------------------------------------
	float scale;
	XY dot;
	RGB color;
	std::vector<History> history;
};
