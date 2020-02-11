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
	dot.setPosition(this->dot.getX() , this->dot.getY());
	dot.scale(this->scale.GetValueX(), this->scale.GetValueY());
	dot.rotate(this->angle.GetValue());
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
	this->SetScale(Scale(scale.GetValueX() + this->scale.GetValueY()));
}

void Point::SetColor(RGB rgb) {
	this->color = rgb;
}

void Point::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
	//else throw...
}

void Point::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
}

Point::~Point() = default;