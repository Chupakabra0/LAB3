#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 
#include "RGB.h"															 
#include "Scale.h"															 															 			 
#include "Angle.h"
#include "Dot.h"
#include "History.h"

class Point : public IDraw
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, RGB color);
	Point(XY xy, RGB color);
	//---------------------------------------------------------------------
	void Draw() override;
	//---------------------------------------------------------------------
	void Previous();
	//---------------------------------------------------------------------
	Scale GetScale() const;
	Angle GetAngle() const;
	Dot GetDot() const;
	RGB GetColor() const;
	//---------------------------------------------------------------------
	void SetScale(const Scale& scale);
	void SetAngle(const Angle& angle);
	void SetDot(const Dot& dot);
	void SetColor(const RGB& color);
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void SetScaleWithoutR(const Scale& scale);
	void SetAngleWithoutR(const Angle& angle);
	void SetDotWithoutR(const Dot& dot);
	void SetColorWithoutR(const RGB& color);
	//---------------------------------------------------------------------
	void Remember();
	//---------------------------------------------------------------------
	Scale scale;
	Angle angle;
	Dot dot;
	RGB color;
	std::vector<History> history;
};
