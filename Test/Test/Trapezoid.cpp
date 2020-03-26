#include "Trapezoid.h"
#include "ShapeDealer.h"

Trapezoid::Trapezoid(float x, float radius): Trapezoid(x, x, radius) {}
Trapezoid::Trapezoid(float x, float y, float radius): Trapezoid(x, y, sf::Color::Magenta, radius) {}
Trapezoid::Trapezoid(float x, float y, sf::Color color, float radius): Trapezoid(XY(x, y), color, radius) {}
Trapezoid::Trapezoid(XY xy, sf::Color color, float radius): Figure(xy, color, radius) {
		this->pic.setPointCount(4);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Trapezoid::Draw(sf::RenderWindow& window) {

	this->pic.setPoint(0, sf::Vector2f(-1.6f * this->radius, this->radius));
	this->pic.setPoint(1, sf::Vector2f(-0.8f * this->radius, -this->radius));
	this->pic.setPoint(2, sf::Vector2f(0.8f * this->radius, -this->radius));
	this->pic.setPoint(3, sf::Vector2f(1.6f * this->radius, this->radius));


	if (this->GetVisible()) {
		this->pic.setFillColor(this->color);
	}
	else {
		this->pic.setFillColor(sf::Color::Transparent);
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
sf::ConvexShape Trapezoid::GetPicture() const {
	return this->pic;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* Trapezoid::Copy() {
	return new Trapezoid(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Trapezoid::~Trapezoid() = default;