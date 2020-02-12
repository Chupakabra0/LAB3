#include "History.h"
#include <SFML/Graphics.hpp>
#include "Circle.h"

using namespace sf;

Circle::Circle(float x): Circle(x, x) {}
Circle::Circle(float x, float y): Circle(x, y, Color(255, 255, 255 , 255)) {}
Circle::Circle(float x, float y, Color color) : Circle(XY(x, y), color) { }

Circle::Circle(XY xy, Color color) : dot(xy), color(color), scale(1.f) {
	this->Circle::RememberCondition();
}

void Circle::Draw(RenderWindow& window) {
	CircleShape dot(1);
	dot.setPosition(this->dot.getX() , this->dot.getY());
	dot.scale(this->scale.GetValueX(), this->scale.GetValueY());
	dot.rotate(this->angle.GetValue());
	window.draw(dot);
}

void Circle::SetPosition(XY xy) {
	this->dot.setXY(xy.getX(), xy.getY());
}

void Circle::ChangePosition(XY xy) {
	this->SetPosition(XY(xy.getX() + this->dot.getX(), xy.getY() + this->dot.getY()));
}

void Circle::SetScale(Scale scale) {
	this->scale = scale;
}

void Circle::ChangeScale(Scale scale) {
	this->SetScale(Scale(scale.GetValueX() + this->scale.GetValueY()));
}

void Circle::SetColor(sf::Color rgb) {
	this->color = rgb;
}

void Circle::PreviousCondition() {
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
	//else throw...
}

void Circle::RememberCondition() {
	this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
}

void Circle::FirstCondition()
{
	if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
	if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
	if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
	this->history.clear();
	this->RememberCondition();
}

Circle::~Circle() = default;