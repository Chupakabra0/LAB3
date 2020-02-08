#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 
#include "RGB.h"															 
#include "Scale.h"															 															 			 
#include "Dot.h"
#include "History.h"

class Point : public IDraw, public IHistory
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
	void PreviousCondition() override;
	//---------------------------------------------------------------------
	Scale GetScale() const;
	Dot GetDot() const;
	RGB GetColor() const;
	//---------------------------------------------------------------------
	void SetScale(const Scale& scale);
	void SetDot(const Dot& dot);
	void SetColor(const RGB& color);
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void SetScaleWithoutR(const Scale& scale);
	void SetDotWithoutR(const Dot& dot);
	void SetColorWithoutR(const RGB& color);
	//---------------------------------------------------------------------
	void RememberCondition() override;
	//---------------------------------------------------------------------
	Scale scale;
	Dot dot;
	RGB color;
	std::vector<History> history;
};
