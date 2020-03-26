#pragma once

#include "Interfaces.h"														 
#include "History.h"
#include "Figure.h"
#include "ShapeDealer.h"

class Diamond : public Figure
{
public:
	Diamond() = delete;
	Diamond(float x, float radius) : Diamond(x, x, radius) {}
	Diamond(float x, float y, float radius) : Diamond(x, y, sf::Color::Green, radius) {}
	Diamond(float x, float y, sf::Color color, float radius) : Diamond(XY(x, y), color, radius) {}
	Diamond(XY xy, sf::Color color, float radius) : Figure(xy, color, radius) {}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Diamond() = default;
private:
	void Draw(sf::RenderWindow& window) override {

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
	Figure* Copy() override {
		return new Diamond(*this);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::CircleShape GetPicture() const {
		return this->pic;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::CircleShape pic;
};
