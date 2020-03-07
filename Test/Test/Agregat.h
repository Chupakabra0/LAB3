#pragma once
#include "History.h"
#include "Circle.h"
#include <utility>
#include <vector>

class Agregat : public Figure {
public:
	Agregat() = delete;
	Agregat(std::vector<Figure*> figures) : figures(std::move(figures)) {}

	virtual ~Agregat() = default;
protected:
	void Draw(sf::RenderWindow& window, std::vector<Figure*>& shapes) override {
		for (auto& element : this->figures) {
			element->Draw(window, shapes);
		}
	}

	XY GetPosition() override {
		return this->dot;
	}
	void SetPosition(XY xy) override {
		for (auto& element : this->figures) {
			element->SetPosition(xy);
		}
	}
	void ChangePosition(XY xy) override {
		for (auto& element : this->figures) {
			element->ChangePosition(xy);
		}
	}

	void SetScale(Scale scale) override {
		for (auto& element : this->figures) {
			element->SetScale(scale);
		}
	}
	void ChangeScale(Scale scale) override {
		for (auto& element : this->figures) {
			element->ChangeScale(scale);
		}
	}

	void SetAngle(Angle angle) override {
		for (auto& element : this->figures) {
			element->SetAngle(angle);
		}
	}
	void ChangeAngle(Angle angle) override {
		for (auto& element : this->figures) {
			element->ChangeAngle(angle);
		}
	}

	void PreviousCondition() override {
		for (auto& element : this->figures) {
			element->PreviousCondition();
		}
	}
	void RememberCondition() override {
		for (auto& element : this->figures) {
			element->RememberCondition();
		}
	}
	void FirstCondition() override {
		for (auto& element : this->figures) {
			element->FirstCondition();
		}
	}

	void SetColor(sf::Color rgba) override {
		for (auto& element : this->figures) {
			element->SetColor(rgba);
		}
	}
private:
	std::vector<Figure*> figures;
};