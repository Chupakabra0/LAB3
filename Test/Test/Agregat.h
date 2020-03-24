#pragma once
#include "History.h"
#include "Circle.h"
#include <utility>
#include <vector>
#include "ShapeDealer.h"

class Agregat : public Figure {
public:
	Agregat() = delete;
	Agregat(const Agregat& copy) : Agregat(copy.getFigures()) {}
	Agregat(std::vector<Figure*> figures) : figures(std::move(figures)) {
		this->centerPos();
	}

	virtual ~Agregat() = default;
protected:
	void Draw(sf::RenderWindow& window) override {
		for (auto& element : this->figures) {
			if (this->isFocused && !element->GetFocus()) ShapeDealer::SwitchFocus(element);
			else if (!this->isFocused && element->GetFocus()) ShapeDealer::SwitchFocus(element);
			element->Draw(window);
		}
	}

	XY GetPosition() override {
		return this->dot;
	}
	void SetPosition(XY xy) override {
		for (auto& element : this->figures) {
			element->SetPosition(xy);
		}
		this->centerPos();
	}
	void ChangePosition(XY xy) override {
		for (auto& element : this->figures) {
			element->ChangePosition(xy);
		}
		this->centerPos();
	}

	void SetScale(Scale scale) override {
		for (auto& element : this->figures) {
			element->SetScale(scale);
		}
		this->scale = scale;
	}
	void ChangeScale(Scale scale) override {
		for (auto& element : this->figures) {
			element->ChangeScale(scale);
		}
		this->scale = Scale(XY(this->scale.GetValueX() + scale.GetValueX(), this->scale.GetValueY() + scale.GetValueY()));
	}

	void SetAngle(Angle angle) override {
		for (auto& element : this->figures) {
			element->SetAngle(angle);
		}
		this->angle = angle;
	}
	void ChangeAngle(Angle angle) override {
		for (auto& element : this->figures) {
			element->ChangeAngle(angle);
		}
		this->angle = Angle(this->angle.GetValue() + angle.GetValue());
	}

	void PreviousCondition() override {
		for (auto& element : this->figures) {
			element->PreviousCondition();
		}
		if (this->history.size() > 1) {
			this->history.pop_back();
			const auto size = this->history.size() - 1;
			if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
			if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
			if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
		}
	}
	void RememberCondition() override {
		for (auto& element : this->figures) {
			element->RememberCondition();
		}
		this->history.emplace_back(History(this->dot, this->scale, this->angle, this->color));
	}
	void FirstCondition() override {
		for (auto& element : this->figures) {
			element->FirstCondition();
		}
		if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
		if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
		if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
		this->history.clear();
		this->RememberCondition();
	}

	void SetColor(sf::Color rgba) override {
		for (auto& element : this->figures) {
			element->SetColor(rgba);
		}
		this->color = rgba;
	}

	Figure* Copy() override {
		return new Agregat(*this);
	}

	std::vector<Figure*> getFigures() const {
		std::vector<Figure*> temp;
		for (auto element : this->figures) {
			temp.push_back(ShapeDealer::MakeCopy(element));
		}
		return temp;
	}
private:
	std::vector<Figure*> figures;

	void centerPos() {
		this->dot = XY(0.f, 0.f);
		for (auto element : this->figures) {
			this->dot += element->GetPosition();
		}
		if (!this->figures.empty()) this->dot /= this->figures.size();
	}
};