#include "History.h"
#include <SFML/Graphics.hpp>
#include "Circle.h"

using namespace sf;

const float highLimit = 50.f;

Circle::Circle(float x, float radius): Circle(x, x, radius) {}
Circle::Circle(float x, float y, float radius): Circle(x, y, Color(255, 255, 255 , 255), radius) {}
Circle::Circle(float x, float y, Color color, float radius) : Circle(XY(x, y), color, radius) { }

Circle::Circle(XY xy, Color color, float radius) : dot(xy), color(color), scale(1.f), radius(radius) {
	this->Circle::RememberCondition();
}

void Circle::Draw(RenderWindow& window) {
	CircleShape dot(this->radius);
	if (this->getVisible()) {
		dot.setFillColor(this->color);
	}
	else {
		dot.setFillColor(Color::Black);
	}
	dot.rotate(this->angle.GetValue());
	dot.scale(this->scale.GetValueX(), this->scale.GetValueY());

	if (this->getTrace()) {
		const auto size = this->history.size();
		for (auto i = 0; i < size - 1; i++) {
			dot.setPosition(this->history[i].GetDot().getX(), this->history[i].GetDot().getY() + highLimit);
			window.draw(dot);
		}
	}

	dot.setPosition(this->dot.getX(), this->dot.getY() + highLimit);
	if (this->isFocused) {
		dot.setOutlineThickness(1.f / std::max(this->scale.GetValueX(), this->scale.GetValueY()));
		dot.setOutlineColor(Color::Green);
	}
	else {
		dot.setOutlineColor(dot.getFillColor());
	}
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