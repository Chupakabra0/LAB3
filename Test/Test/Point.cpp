#include "Point.h"

Point::Point(float x): Point(x, x) {}
Point::Point(float x, float y): Point(x, y, 0.f) {}
Point::Point(float x, float y, float color) : Point(x, y, RGB(color)) {}
Point::Point(float x, float y, float red, float green, float blue) : Point(x, y, RGB(red, green, blue)) {}

Point::Point(float x, float y, RGB color) : coordinate(x, y), color(color), angle(0.f), scale(1.f) {
	this->Point::RememberPosition(this->coordinate);
	this->Point::RememberAngle(this->angle);
	this->Point::RememberScale(this->scale);
}

void Point::ChangePosition(float dx, float dy) {
	this->coordinate.changeXY(dx, dy);
	this->RememberPosition(this->coordinate);
}

void Point::ChangePosition(XY dxdy) {
	this->coordinate.changeXY(dxdy);
	this->RememberPosition(this->coordinate);
}

void Point::SetPosition(float x, float y) {
	this->coordinate.setXY(x, y);
	this->RememberPosition(this->coordinate);
}

void Point::SetPosition(XY xy) {
	this->coordinate.setXY(xy);
	this->RememberPosition(this->coordinate);
}

void Point::PreviousPosition() {
	if (!this->historyPosition.empty()) {
		this->historyPosition.pop_back();
		this->SetPosition(this->historyPosition[this->historyPosition.size() - 1]);
	}
	//else throw...
}

XY Point::GetPosition() const {
	return this->coordinate;
}

void Point::ChangeAngle(float angle)
{
	this->angle += angle;
	this->RememberAngle(this->angle);
}

void Point::SetAngle(float angle) {
	this->angle = angle;
	this->RememberAngle(this->angle);
}

void Point::PreviousAngle()
{
	if (!this->historyAngel.empty()) {
		this->historyAngel.pop_back();
		SetAngle(this->historyAngel[this->historyAngel.size() - 1]);
	}
	//else throw...
}

float Point::getAngle() const
{
	return this->angle;
}

void Point::ChangeScale(float percent)
{
	this->scale += percent;
	this->RememberScale(this->angle);
}

void Point::SetScale(float percent)
{
	this->scale = percent;
	this->RememberAngle(this->angle);
}

void Point::PreviousScale()
{
	if (!this->historyScale.empty()) {
		this->historyScale.pop_back();
		this->SetScale(this->historyScale[this->historyScale.size() - 1]);
	}
	// else throw...
}

float Point::GetScale() const
{
	return this->scale;
}

RGB Point::GetColor() const
{
	return this->color;
}

Point::~Point() = default;

void Point::RememberPosition(XY xy) {
	this->historyPosition.push_back(xy);
}

void Point::RememberPosition(float x, float y) {
	const XY temp(x, y);
	this->historyPosition.push_back(temp);
}

void Point::RememberAngle(float angle)
{
	this->historyAngel.push_back(angle);
}

void Point::RememberScale(float percent)
{
	this->historyScale.push_back(percent);
}
