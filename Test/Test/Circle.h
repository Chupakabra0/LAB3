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
	Scale GetScale() override {
		return this->scale;
	}
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetColor(sf::Color rgb) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Angle GetAngle() override {
		return this->angle;
	}
	void SetAngle(Angle angle) override {
		this->angle = angle;
	}
	void ChangeAngle(Angle angle) override {
		this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
	}
	//---------------------------------------------------------------------
	sf::CircleShape getPicture() const {
		return this->pic;
	}
	//---------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	void FirstCondition() override;
	//---------------------------------------------------------------------
	Figure* Copy() override {
		return new Circle(*this);
	}
	//---------------------------------------------------------------------
	sf::CircleShape pic;
};