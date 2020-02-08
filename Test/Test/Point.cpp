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
	dot.setPosition(this->dot.getX(), this->dot.getY());
	window.draw(dot);
}

void Point::SetPosition(float xy) {
	this->SetPosition(xy, xy);
}

void Point::SetPosition(float x, float y) {
	this->SetPosition(XY(x, y));
}

void Point::SetPosition(XY xy) {
	this->dot.setXY(xy.getX(), xy.getY());
	this->RememberCondition();
}

void Point::ChangePosition(float xy) {
	this->ChangePosition(xy, xy);
}

void Point::ChangePosition(float x, float y) {
	this->ChangePosition(XY(x, y));
}

void Point::ChangePosition(XY xy) {
	this->SetPosition(XY(xy.getX() + this->dot.getX(), xy.getY() + this->dot.getY()));
}

void Point::SetScale(float scale) {
	this->scale = scale;
	this->RememberCondition();
}

void Point::ChangeScale(float scale) {
	this->SetScale(scale + this->scale);
}

void Point::SetColor(float red, float green, float blue) {
	this->SetColor(RGB(red, green, blue));
}

void Point::SetColor(RGB rgb) {
	this->color = rgb;
	this->RememberCondition();
}


void Point::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->AdminSetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->AdminSetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->AdminSetColor(this->history[size].GetColor());
	}
	//else throw...
}

void Point::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, NULL, this->color);
}

Point::~Point() = default;

void Point::AdminSetPosition(XY xy) {
	this->dot.setXY(xy.getX(), xy.getY());
}

void Point::AdminChangePosition(XY xy) {
	this->AdminSetPosition(XY(this->dot.getX() + xy.getX(), this->dot.getY() + xy.getY()));
}

void Point::AdminSetScale(float scale) {
	this->scale = scale;
}

void Point::AdminChangeScale(float scale) {
	this->AdminSetScale(this->scale + scale);
}

void Point::AdminSetColor(RGB rgb) {
	this->color = rgb;
}
