#pragma once
#include <SFML/Graphics/Color.hpp>

#include "Interfaces.h"
#include "History.h"

struct Figure : virtual IMove, virtual IScale, virtual IDraw, virtual IRotate {
	Figure();
	Figure(XY xy);
	Figure(XY xy, float radius);
	Figure(XY xy, sf::Color rgba);
	Figure(XY xy, sf::Color rgba, float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool GetFocus() const;
	void SetFocus(bool focus);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool GetVisible() const;
	void SetVisible(bool visible);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool GetTrace() const;
	void SetTrace(bool trace);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool GetTouch() const;
	void SetTouch(bool touch);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	size_t GetTraceNum() const;
	void SetTraceNum(size_t trace);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	std::vector<History> GetHistory() const;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	float GetRadius() const;
	void SetRadius(float radius);
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