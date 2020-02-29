#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 														 
#include "History.h"

struct Figure : IMove, IScale, IDraw, IRotate {
	Figure() {
		this->setFocus(false);
		this->setVisible(true);
	}
	virtual ~Figure() = default;

	bool getFocus() const {
		return this->isFocused;
	}
	void setFocus(bool focus) {
		set(this->isFocused, focus);
	}

	bool getVisible() const {
		return this->isVisible;
	}
	void setVisible(bool visible) {
		set(this->isVisible, visible);
	}
protected:
	bool isFocused;
	bool isVisible;
private:
	static void set(bool& first, const bool& second) {
		if (first != second) first = second;
	}
};

class Circle : public Figure
{
public:
	Circle() = delete;
	Circle(float x, float radius);
	Circle(float x, float y, float radius);
	Circle(float x, float y, sf::Color color, float radius);
	Circle(XY xy, sf::Color color, float radius);
	virtual ~Circle();
protected:
	void Draw(sf::RenderWindow& window) override;
	//---------------------------------------------------------------------
	void SetPosition(XY xy) override;
	void ChangePosition(XY xy) override;
	//---------------------------------------------------------------------
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//---------------------------------------------------------------------
	void SetColor(sf::Color rgb) override;
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
	void FirstCondition() override;
	//---------------------------------------------------------------------
	Scale scale;
	Angle angle;
	XY dot;
	float radius;
	sf::Color color;
	std::vector<History> history;
};
