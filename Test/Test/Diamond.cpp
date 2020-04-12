#include "Diamond.h"
#include "ShapeDealer.h"

Diamond::Diamond(float x, float radius): Diamond(x, x, radius) {}
Diamond::Diamond(float x, float y, float radius): Diamond(x, y, sf::Color::Green, radius) {}
Diamond::Diamond(float x, float y, sf::Color color, float radius): Diamond(XY(x, y), color, radius) {}
Diamond::Diamond(XY xy, sf::Color color, float radius): Figure(xy, color, radius) {}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Diamond::Draw(sf::RenderWindow& window) {

	this->pic.setPointCount(4);

	this->pic.setRadius(this->radius);

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

Diamond* Diamond::Copy() {
	return new Diamond(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
sf::Shape* Diamond::GetPicture() {
	return &this->pic;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Diamond::~Diamond() = default;