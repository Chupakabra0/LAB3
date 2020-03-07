#include "History.h"
#include <SFML/Graphics.hpp>
#include "Circle.h"

using namespace sf;

const float highLimit = 50.f;

Circle::Circle(float x, float radius): Circle(x, x, radius) {}
Circle::Circle(float x, float y, float radius): Circle(x, y, Color(255, 255, 255 , 255), radius) {}
Circle::Circle(float x, float y, Color color, float radius) : Circle(XY(x, y), color, radius) { }

Circle::Circle(XY xy, Color color, float radius) : dot(xy), color(color), scale(1.f), angle(0.f), radius(radius) {
	this->Circle::RememberCondition();
}

void Circle::Draw(RenderWindow& window, std::vector<Figure*>& shapes) {
	this->pic.setRadius(this->radius);
	if (this->getVisible()) {
		this->pic.setFillColor(this->color);
	}
	else {
		this->pic.setFillColor(Color::Black);
	}

	this->pic.rotate(this->angle.GetValue());
	this->pic.setScale(this->scale.GetValueX(), this->scale.GetValueY());

	for (auto& element : shapes) {
		if (element != this
			&&
			pow(this->dot.getX() - element->GetPosition().getX(), 2) + pow(this->dot.getY() - element->GetPosition().getY(), 2) <= pow(this->radius, 2)
			) {
			this->pic.setScale(this->scale.GetValueX() + 10.f, this->scale.GetValueY());
			break;
		}
	}

	if (this->getTrace()) {
		const auto size = this->history.size();
		for (auto i = this->getTraceNum(); i < size - 1; i++) {
			this->pic.setPosition(this->history[i].GetDot().getX(), this->history[i].GetDot().getY() + highLimit);
			window.draw(this->pic);
		}
	}

	this->pic.setPosition(this->dot.getX(), this->dot.getY() + highLimit);
	if (this->isFocused) {
		this->pic.setOutlineThickness(1.f / std::max(this->scale.GetValueX(), this->scale.GetValueY()));
		this->pic.setOutlineColor(Color::Green);
	}
	else {
		this->pic.setOutlineColor(this->pic.getFillColor());
	}
	window.draw(this->pic);
}

XY Circle::GetPosition()
{
	return this->dot;
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