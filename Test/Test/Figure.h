#pragma once
#include <SFML/Graphics/Color.hpp>
#include "Interfaces.h"
#include "History.h"

struct Figure : virtual IMove, virtual IScale, virtual IDraw, virtual IRotate {
	Figure();
	Figure(XY xy);
	Figure(XY xy, float radius);
	Figure(XY xy, sf::Color rgba);
	Figure(XY xy, float radius, sf::Color rgba);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool getFocus() const;
	void setFocus(bool focus);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool getVisible() const;
	void setVisible(bool visible);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool getTrace() const;
	void setTrace(bool trace);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool getTouch() const;
	void setTouch(bool touch);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	size_t getTraceNum() const;
	void setTraceNum(size_t trace);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	std::vector<History> getHistory() const;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	float getRadius() const;
	void setRadius(float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual Figure* Copy() abstract;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Figure();
protected:
	bool isFocused{};
	bool isVisible{};
	bool isTraced{};
	bool isTouched{};
	size_t trace;
	std::vector<History> history;
	XY dot;
	Scale scale;
	Angle angle;
	sf::Color color;
	float radius;
private:
	static void set(bool& first, const bool& second);
};