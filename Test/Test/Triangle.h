#pragma once
#include "Figure.h"
#include "ShapeDealer.h"

class Triangle : public Figure
{
public:
	Triangle() = delete;
	Triangle(float x, float radius) : Triangle(x, x, radius) {}
	Triangle(float x, float y, float radius) : Triangle(x, y, sf::Color::Blue, radius) {}
	Triangle(float x, float y, sf::Color color, float radius) : Triangle(XY(x, y), color, radius) {}
	Triangle(XY xy, sf::Color color, float radius) : Figure(xy, color, radius) {
		this->Triangle::RememberCondition();
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Triangle() = default;
protected:
	void Draw(sf::RenderWindow& window) override {
		this->pic.setPointCount(3);

		this->pic.setRadius(this->radius);

		if (this->GetVisible()) {
			this->pic.setFillColor(this->color);
		}
		else {
			this->pic.setFillColor(sf::Color::Black);
		}

		this->pic.setOutlineColor(this->color);

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
	XY GetPosition() override {
		return this->dot;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetPosition(XY xy) override {
		this->dot.SetXY(xy.GetX(), xy.GetY());
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void ChangePosition(XY xy) override {
		this->SetPosition(XY(xy.GetX() + this->dot.GetX(), xy.GetY() + this->dot.GetY()));
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Angle GetAngle() override {
		return this->angle;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetAngle(Angle angle) override {
		this->angle = angle;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void ChangeAngle(Angle angle) override {
		this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::CircleShape GetPicture() const {
		return this->pic;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Figure* Copy() override {
		return new Triangle(*this);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Scale GetScale() override {
		return this->scale;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetScale(Scale scale) override {
		this->scale = scale;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void ChangeScale(Scale scale) override {
		this->SetScale(Scale(scale.GetX() + this->scale.GetY()));
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Color GetColor() override {
		return this->color;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetColor(sf::Color rgb) override {
		this->color = rgb;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void PreviousCondition() override {
		if (this->history.size() > 1) {
			this->history.pop_back();
			const auto size = this->history.size() - 1;
			if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
			if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
			if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
		}
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void RememberCondition() override {
		this->history.emplace_back(this->dot, this->scale, this->angle, this->color);
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void FirstCondition() override {
		if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
		if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
		if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
		this->history.clear();
		this->RememberCondition();
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::CircleShape pic;
};
