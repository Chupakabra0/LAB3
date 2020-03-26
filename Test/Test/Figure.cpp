#include "Figure.h"

Figure::Figure(): Figure(XY(0)) {}
Figure::Figure(XY xy): Figure(xy, sf::Color::Red) {}
Figure::Figure(XY xy, float radius): Figure(xy, sf::Color::Red, radius) {}
Figure::Figure(XY xy, sf::Color rgba): Figure(xy, rgba, 10.f) {}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure::Figure(XY xy, sf::Color rgba, float radius) : trace(0), dot(xy), scale(1.f), angle(0.f), color(rgba), radius(radius) {
	this->SetFocus(false);
	this->SetTrace(false);
	this->SetTouch(false);
	this->SetVisible(true);
	this->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
bool Figure::GetFocus() const {
	return this->isFocused;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetFocus(bool focus) {
	set(this->isFocused, focus);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
bool Figure::GetVisible() const {
	return this->isVisible;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetVisible(bool visible) {
	set(this->isVisible, visible);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
bool Figure::GetTrace() const {
	return this->isTraced;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetTrace(bool trace) {
	set(this->isTraced, trace);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
bool Figure::GetTouch() const {
	return this->isTouched;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetTouch(bool touch) {
	set(this->isTouched, touch);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
size_t Figure::GetTraceNum() const {
	return this->trace;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetTraceNum(size_t trace) {
	this->trace = trace;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
std::vector<History> Figure::GetHistory() const {
	return this->history;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetRadius(float radius) {
	this->radius = radius;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
XY Figure::GetPosition() {
	return this->dot;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetPosition(XY xy) {
	this->dot.SetXY(xy.GetX(), xy.GetY());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::ChangePosition(XY xy) {
	this->SetPosition(XY(xy.GetX() + this->dot.GetX(), xy.GetY() + this->dot.GetY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Angle Figure::GetAngle() {
	return this->angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetAngle(Angle angle) {
	this->angle = angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::ChangeAngle(Angle angle) {
	this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Scale Figure::GetScale() {
	return this->scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetScale(Scale scale) {
	this->scale = scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::ChangeScale(Scale scale) {
	this->SetScale(Scale(scale.GetX() + this->scale.GetY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
sf::Color Figure::GetColor() {
	return this->color;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::SetColor(sf::Color rgb) {
	this->color = rgb;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::FirstCondition() {
	if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
	if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
	if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
	this->history.clear();
	this->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
float Figure::GetRadius() const {
	return this->radius;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Figure::set(bool& first, const bool& second) {
	if (first != second) first = second;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure::~Figure() = default;