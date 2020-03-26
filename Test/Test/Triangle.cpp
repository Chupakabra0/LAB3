#include "Triangle.h"

Triangle::Triangle(float x, float radius): Triangle(x, x, radius) {}
Triangle::Triangle(float x, float y, float radius): Triangle(x, y, sf::Color::Blue, radius) {}
Triangle::Triangle(float x, float y, sf::Color color, float radius): Triangle(XY(x, y), color, radius) {}

Triangle::Triangle(XY xy, sf::Color color, float radius): Figure(xy, color, radius) {
	this->Triangle::RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::Draw(sf::RenderWindow& window) {
	this->pic.setPointCount(3);

	this->pic.setRadius(this->radius);

	if (this->GetVisible()) {
		this->pic.setFillColor(this->color);
	}
	else {
		this->pic.setFillColor(sf::Color::Transparent);
	}

	this->pic.setOutlineColor(this->color);

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
XY Triangle::GetPosition() {
	return this->dot;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::SetPosition(XY xy) {
	this->dot.SetXY(xy.GetX(), xy.GetY());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::ChangePosition(XY xy) {
	this->SetPosition(XY(xy.GetX() + this->dot.GetX(), xy.GetY() + this->dot.GetY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Angle Triangle::GetAngle() {
	return this->angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::SetAngle(Angle angle) {
	this->angle = angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::ChangeAngle(Angle angle) {
	this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
sf::CircleShape Triangle::GetPicture() const {
	return this->pic;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* Triangle::Copy() {
	return new Triangle(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Scale Triangle::GetScale() {
	return this->scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::SetScale(Scale scale) {
	this->scale = scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::ChangeScale(Scale scale) {
	this->SetScale(Scale(scale.GetX() + this->scale.GetY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
sf::Color Triangle::GetColor() {
	return this->color;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::SetColor(sf::Color rgb) {
	this->color = rgb;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Triangle::FirstCondition() {
	if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
	if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
	if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
	this->history.clear();
	this->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Triangle::~Triangle() = default;