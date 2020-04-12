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
	virtual void SetVisible(bool visible);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool GetTrace() const;
	virtual void SetTrace(bool trace);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	bool GetTouch() const;
	virtual void SetTouch(bool touch);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	size_t GetTraceNum() const;
	void SetTraceNum(size_t trace);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	std::vector<History> GetHistory() const;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	float GetRadius() const;
	virtual void SetRadius(float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	XY GetPosition() override;
	void SetPosition(XY xy) override;
	void ChangePosition(XY xy) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Angle GetAngle() override;
	void SetAngle(Angle angle) override;
	void ChangeAngle(Angle angle) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Scale GetScale() override;
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Color GetColor() override;
	void SetColor(sf::Color rgb) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	void FirstCondition() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual Figure* Copy() abstract;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual bool Intersects(Figure* shape);
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