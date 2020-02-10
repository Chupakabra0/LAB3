#include "Point.h"
#include "History.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, 0.f) {}
Point::Point(float x, float y, RGB color) : Point(XY(x, y), color) { }

Point::Point(XY xy, RGB color) : dot(xy), color(color), scale(1.f) {
	this->Point::RememberCondition();
}

void Point::Draw(RenderWindow& window) {
	CircleShape dot(1);
	const auto x = (this->dot.getX() - this->dot.getX() - 10) * cos(this->angle.GetValue()) - (this->dot.getY() - this->dot.getX()- 10) * sin(this->angle.GetValue()) + (this->dot.getX() + 10);
	const auto y = (this->dot.getX() - this->dot.getX() - 10) * sin(this->angle.GetValue()) + (this->dot.getY() - this->dot.getX() - 10) * cos(this->angle.GetValue()) + (this->dot.getY() + 10);
	dot.setPosition(x, y);
	window.draw(dot);
}

void Point::SetPosition(XY xy) {
	this->dot.setXY(xy.getX(), xy.getY());
}

void Point::ChangePosition(XY xy) {
	this->SetPosition(XY(xy.getX() + this->dot.getX(), xy.getY() + this->dot.getY()));
}

void Point::SetScale(Scale scale) {
	this->scale = scale;
}

void Point::ChangeScale(Scale scale) {
	this->SetScale(Scale(scale.GetValue() + this->scale.GetValue()));
}

void Point::SetColor(RGB rgb) {
	this->color = rgb;
}

void Point::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale.GetValue() != this->history[size].GetScale().GetValue()) this->SetScale(this->history[size].GetScale().GetValue());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
	//else throw...
}

void Point::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, NULL, this->color);
}

Point::~Point() = default;