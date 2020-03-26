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
	XY GetPosition() override {
		return this->dot;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetPosition(XY xy) override {
		this->dot.SetXY(xy.GetX(), xy.GetY());
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void ChangePosition(XY xy) override {
		this->SetPosition(XY(xy.GetX() + this->dot.GetX(), xy.GetY() + this->dot.GetY()));
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Angle GetAngle() override {
		return this->angle;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetAngle(Angle angle) override {
		this->angle = angle;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void ChangeAngle(Angle angle) override {
		this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Scale GetScale() override {
		return this->scale;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetScale(Scale scale) override {
		this->scale = scale;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void ChangeScale(Scale scale) override {
		this->SetScale(Scale(scale.GetX() + this->scale.GetY()));
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Color GetColor() override {
		return this->color;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetColor(sf::Color rgb) override {
		this->color = rgb;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void PreviousCondition() override {
		if (this->history.size() > 1) {
			this->history.pop_back();
			const auto size = this->history.size() - 1;
			if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
			if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
			if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void RememberCondition() override {
		this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void FirstCondition() override {
		if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
		if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
		if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
		this->history.clear();
		this->RememberCondition();
	}
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