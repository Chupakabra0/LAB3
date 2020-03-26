#include <SFML/Graphics.hpp>

#include "Circle.h"
#include "History.h"
#include "ShapeDealer.h"

using namespace sf;

Circle::Circle(float x, float radius): Circle(x, x, radius) {}
Circle::Circle(float x, float y, float radius): Circle(x, y, Color(255, 255, 255 , 255), radius) {}
Circle::Circle(float x, float y, Color color, float radius) : Circle(XY(x, y), color, radius) { }
//-----------------------------------------------------------------------------------------------------------------------------------------------
Circle::Circle(XY xy, Color color, float radius) : Figure(xy, color, radius) {
	this->Circle::RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::Draw(RenderWindow& window) {

	this->pic.setRadius(this->radius);

	if (this->GetVisible()) {
		this->pic.setFillColor(this->color);
	}
	else {
		this->pic.setFillColor(Color::Black);
	}

	this->pic.setOutlineColor(this->pic.getFillColor());

	if (this->isTouched) {
		this->pic.setScale(this->scale.GetX() + 2, this->scale.GetY() + 2);
	}
	else {
		this->pic.setScale(this->scale.GetX(), this->scale.GetY());
	}
	
	this->pic.setRotation(this->angle.GetValue());

	if (this->GetTrace()) {
		const auto size = this->history.size();
		for (auto i = this->GetTraceNum(); i < size - 1; i++) {
			this->pic.setPosition(this->history[i].GetDot().GetX(), this->history[i].GetDot().GetY());
			window.draw(this->pic);
		}
	}

	this->pic.setPosition(this->dot.GetX(), this->dot.GetY());

	if (this->isFocused) {
		this->pic.setOutlineThickness(1.f / std::max(this->scale.GetX(), this->scale.GetY()));
		this->pic.setOutlineColor(ShapeDealer::ReverseColor(this->color));
	}
	else {
		this->pic.setOutlineColor(this->pic.getFillColor());
	}
	window.draw(this->pic);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
XY Circle::GetPosition() {
	return this->dot;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::SetPosition(XY xy) {
	this->dot.SetXY(xy.GetX(), xy.GetY());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::ChangePosition(XY xy) {
	this->SetPosition(XY(xy.GetX() + this->dot.GetX(), xy.GetY() + this->dot.GetY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Angle Circle::GetAngle() {
	return this->angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::SetAngle(Angle angle) {
	this->angle = angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::ChangeAngle(Angle angle) {
	this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
CircleShape Circle::GetPicture() const {
	return this->pic;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* Circle::Copy() {
	return new Circle(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Scale Circle::GetScale() {
	return this->scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::SetScale(Scale scale) {
	this->scale = scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::ChangeScale(Scale scale) {
	this->SetScale(Scale(scale.GetX() + this->scale.GetY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Color Circle::GetColor() {
	return this->color;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::SetColor(sf::Color rgb) {
	this->color = rgb;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Circle::FirstCondition() {
	if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
	if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
	if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
	this->history.clear();
	this->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Circle::~Circle() = default;