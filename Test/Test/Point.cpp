#include "Point.h"

Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, 0.f) {}
Point::Point(float x, float y, RGB color) : Point(XY(x, y), color){  }

Point::Point(XY xy, RGB color) : dot(xy), color(color), angle(0.f), scale(1.f) {
	this->Remember();
}

void Point::Draw() {}

void Point::Previous() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->GetDot() != this->history[size].GetDot()) this->dot = Dot(this->history[size].GetDot());
		if (this->GetAngle() != this->history[size].GetAngle()) this->angle = Angle(this->history[size].GetAngle());
		if (this->GetScale() != this->history[size].GetScale()) this->scale = Scale(this->history[size].GetScale());  //TODO добавить приватный сеттер без запоминания истории
		if (this->GetColor() != this->history[size].GetColor()) this->color = RGB(this->history[size].GetColor());
	}
	//else throw...
}

Scale Point::GetScale() const { return this->scale; }

Angle Point::GetAngle() const { return this->angle; }

Dot Point::GetDot() const { return this->dot; }

RGB Point::GetColor() const {
	return this->color;
}

void Dot::SetPosition(float x, float y) {
	this->dot.setXY(x, y);
}

void Dot::SetPosition(XY xy) {
	this->dot.setXY(xy);
}

XY Dot::GetPosition() const {
	return this->dot;
}

void Angle::SetAngle(float angle) {
	this->angle = angle;
}

float Angle::GetAngle() const {
	return this->angle;
}

void Scale::ChangeScale(float percent)
{
	this->scale += percent;
}

void Scale::SetScale(float percent)
{
	this->scale = percent;
}

float Scale::GetScale() const {
	return this->scale;
}

void Point::Remember() {
	this->history.emplace_back(this->GetDot(), this->GetScale(), this->GetAngle(), this->GetColor());
}

Point::~Point() = default;