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
		this->pic.setFillColor(Color::Transparent);
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
CircleShape Circle::GetPicture() const {
	return this->pic;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* Circle::Copy() {
	return new Circle(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Circle::~Circle() = default;