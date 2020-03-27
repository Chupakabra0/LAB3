#pragma once
#include <vector>

#include "Figure.h"

class Agregat : public Figure {
public:
	Agregat() = delete;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Agregat(const Agregat& copy);
	Agregat(std::vector<Figure*> figures);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	std::vector<Figure*> GetFigures() const;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Agregat();
protected:
	void Draw(sf::RenderWindow& window) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	XY GetPosition() override;
	void SetPosition(XY xy) override;
	void ChangePosition(XY xy) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Scale GetScale() override;
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Angle GetAngle() override;
	void SetAngle(Angle angle) override;
	void ChangeAngle(Angle angle) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	void FirstCondition() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Color GetColor() override;
	void SetColor(sf::Color rgba) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Figure* Copy() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Shape* GetPicture() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetRadius(float radius) override {
		for (auto& element : this->figures) {
			element->SetRadius(radius);
		}
		if (this->radius != radius) this->radius = radius;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetTouch(bool touch) override {
		for (auto& element : this->figures) {
			element->SetTouch(touch);
		}
		if (this->isTouched != touch) this->isTouched = touch;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetTrace(bool trace) override {
		for (auto& element : this->figures) {
			element->SetTrace(trace);
		}
		if (this->isTraced != trace) this->isTraced = trace;
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	void SetVisible(bool visible) override {
		for (auto& element : this->figures) {
			element->SetVisible(visible);
		}
		if (this->isVisible != trace) this->isVisible = visible;
	}
private:
	void CenterPos();
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	std::vector<Figure*> figures;
};
