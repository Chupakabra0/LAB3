#include "Point.h"
#include "Scale.h"
#include "Angle.h"
#include "History.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, 0.f) {}
Point::Point(float x, float y, RGB color) : Point(XY(x, y), color){  }

Point::Point(XY xy, RGB color) : dot(xy), color(color), angle(0.f), scale(1.f) {
	this->Remember();
}

void Point::Draw(RenderWindow& window) {
	CircleShape dot(1);
	dot.setPosition(this->GetDot().GetPosition().getX(), this->GetDot().GetPosition().getY());
	window.draw(dot);
}

void Point::Previous() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->GetDot() != this->history[size].GetDot()) this->SetDotWithoutR(this->history[size].GetDot());
		if (this->GetAngle() != this->history[size].GetAngle()) this->SetAngleWithoutR(this->history[size].GetAngle());
		if (this->GetScale() != this->history[size].GetScale()) this->SetScaleWithoutR(this->history[size].GetScale());
		if (this->GetColor() != this->history[size].GetColor()) this->SetColorWithoutR(this->history[size].GetColor());
	}
	//else throw...
}

Scale Point::GetScale() const { return this->scale; }

Angle Point::GetAngle() const { return this->angle; }

Dot Point::GetDot() const { return this->dot; }

RGB Point::GetColor() const {
	return this->color;
}

void Point::SetScale(const Scale& scale) {
	this->scale.SetScale(scale.GetScale());
	this->Remember();
}

void Point::SetAngle(const Angle& angle) {
	this->angle.SetAngle(angle.GetAngle());
	this->Remember();
}

void Point::SetDot(const Dot& dot) {
	this->dot.SetPosition(dot.GetPosition());
	this->Remember();
}

void Point::SetColor(const RGB& color) {
	this->color.setRGB(color.getR(), color.getG(), color.getB());
	this->Remember();
}

void Point::Remember() {
	this->history.emplace_back(this->GetDot(), this->GetScale(), this->GetAngle(), this->GetColor());
}

Point::~Point() = default;
void Point::SetScaleWithoutR(const Scale& scale) { this->scale.SetScale(scale.GetScale()); }

void Point::SetAngleWithoutR(const Angle& angle) { this->angle.SetAngle(angle.GetAngle()); }

void Point::SetDotWithoutR(const Dot& dot) { this->dot.SetPosition(dot.GetPosition()); }

void Point::SetColorWithoutR(const RGB& color) { this->color.setRGB(color.getR(), color.getG(), color.getB()); }
