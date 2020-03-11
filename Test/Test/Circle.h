#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 														 
#include "History.h"

struct Figure : virtual IMove, virtual IScale, virtual IDraw, virtual IRotate {
	Figure() : Figure(XY(0)) {}
	Figure(XY xy) : Figure(xy , sf::Color::Red) {}
	Figure(XY xy, float radius) : Figure(xy, radius, sf::Color::Red) {}
	Figure(XY xy, sf::Color rgba) : Figure(xy, 10.f, rgba) {}
	Figure(XY xy, float radius, sf::Color rgba) : trace(0), dot(xy), scale(1.f), angle(0.f), color(rgba), radius(radius) {
		this->setFocus(false);
		this->setTrace(false);
		this->setTouch(false);
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

	bool getTrace() const {
		return this->isTraced;
	}
	void setTrace(bool trace) {
		set(this->isTraced, trace);
	}


	bool getTouch() const {
		return this->isTouched;
	}
	void setTouch(bool touch) {
		set(this->isTouched, touch);
	}

	size_t getTraceNum() const {
		return this->trace;
	}
	void setTraceNum(size_t trace) {
		this->trace = trace;
	}

	std::vector<History> getHistory() const {
		return this->history;
	}

	void setRadius(float radius) {
		this->radius = radius;
	}
	float getRadius() const {
		return this->radius;
	}

	virtual Figure* Copy() abstract;
protected:
	bool isFocused;
	bool isVisible;
	bool isTraced;
	bool isTouched;
	size_t trace;
	std::vector<History> history;
	XY dot;
	Scale scale;
	Angle angle;
	sf::Color color;
	float radius;
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
	XY GetPosition() override;
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