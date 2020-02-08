#include "Point.h"
#include "Scale.h"
#include "History.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, 0.f) {}
Point::Point(float x, float y, RGB color) : Point(XY(x, y), color){  }

Point::Point(XY xy, RGB color) : dot(xy), color(color), scale(1.f) {
	this->Point::RememberCondition();
}

void Point::Draw(RenderWindow& window) {
	CircleShape dot(1);
	dot.setPosition(this->dot.GetPosition().getX(), this->dot.GetPosition().getY());
	window.draw(dot);
}

void Point::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetDotWithoutR(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScaleWithoutR(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColorWithoutR(this->history[size].GetColor());
	}
	//else throw...
}

//Scale Point::GetScale() const { return this->scale; }
//
//Dot Point::GetDot() const { return this->dot; }
//
//RGB Point::GetColor() const {
//	return this->color;
//}

void Point::SetScale(const Scale& scale) {
	this->scale.SetScale(scale.GetScale());
	this->RememberCondition();
}

void Point::SetDot(const Dot& dot) {
	this->dot.SetPosition(dot.GetPosition());
	this->RememberCondition();
}

void Point::SetColor(const RGB& color) {
	this->color.setRGB(color.getR(), color.getG(), color.getB());
	this->RememberCondition();
}

void Point::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, NULL, this->color);
}

Point::~Point() = default;
void Point::SetScaleWithoutR(const Scale& scale) { this->scale.SetScale(scale.GetScale()); }

void Point::SetDotWithoutR(const Dot& dot) { this->dot.SetPosition(dot.GetPosition()); }

void Point::SetColorWithoutR(const RGB& color) { this->color.setRGB(color.getR(), color.getG(), color.getB()); }
