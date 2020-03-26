#include "Star.h"

Star::Star(float x, float radius): Star(x, x, radius) {}
Star::Star(float x, float y, float radius): Star(x, y, sf::Color::Yellow, radius) {}
Star::Star(float x, float y, sf::Color color, float radius): Star(XY(x, y), color, radius) {}
Star::Star(XY xy, sf::Color color, float radius): Figure(xy, color, radius) {
		pic.setPointCount(10);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Star::Draw(sf::RenderWindow& window) {

	this->pic.setPoint(0, sf::Vector2f(1.2f * this->radius, 0));
	this->pic.setPoint(1, sf::Vector2f(1.44f * this->radius, 0.8f * this->radius));
	this->pic.setPoint(2, sf::Vector2f(2.2f * this->radius, 0.8f * this->radius));
	this->pic.setPoint(3, sf::Vector2f(1.6f * this->radius, 1.2f * this->radius));
	this->pic.setPoint(4, sf::Vector2f(2.f * this->radius, 2.f * this->radius));
	this->pic.setPoint(5, sf::Vector2f(1.2f * this->radius, 1.4f * this->radius));
	this->pic.setPoint(6, sf::Vector2f(0.4f * this->radius, 2.f * this->radius));
	this->pic.setPoint(7, sf::Vector2f(0.8f * this->radius, 1.2f * this->radius));
	this->pic.setPoint(8, sf::Vector2f(0.2f * this->radius, 0.8f * this->radius));
	this->pic.setPoint(9, sf::Vector2f(0.96f * this->radius, 0.8f * this->radius));

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
Figure* Star::Copy() {
	return new Star(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
sf::ConvexShape Star::GetPicture() const {
	return this->pic;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Star::~Star() = default;