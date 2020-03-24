#pragma once																 
#include <vector>

#include "Interfaces.h"														 
#include "History.h"
#include "Figure.h"

class Circle : public Figure {
public:
	Circle() = delete;
	Circle(float x, float radius);
	Circle(float x, float y, float radius);
	Circle(float x, float y, sf::Color color, float radius);
	Circle(XY xy, sf::Color color, float radius);
	virtual ~Circle();
protected:
	void Draw(sf::RenderWindow& window) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	XY GetPosition() override;
	void SetPosition(XY xy) override;
	void ChangePosition(XY xy) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Scale GetScale() override;
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetColor(sf::Color rgb) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Angle GetAngle() override;
	void SetAngle(Angle angle) override;
	void ChangeAngle(Angle angle) override;
	//---------------------------------------------------------------------
	sf::CircleShape GetPicture() const;
	//---------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	void FirstCondition() override;
	//---------------------------------------------------------------------
	Figure* Copy() override;
	//---------------------------------------------------------------------
	sf::CircleShape pic;
};