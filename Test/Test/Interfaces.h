#pragma once
#include "XY.h"
#include "RGB.h"
#include <SFML/Graphics.hpp>

class Angle {
public:
	Angle() = default;
	Angle(float angle): angle(angle) {
		AngleRot(*this);
	}
	float GetValue() const {
		return this->angle;
	}
protected:
	static void AngleRot(Angle& angle) {
		while (angle.angle >= 360) {
			angle.angle -= 360;
		}
	}
	float angle;
};

class Scale {
public:
	Scale() = default;
	Scale(float scale) : scale(scale) {}
	float GetValue() const {
		return this->scale;
	}
protected:
	float scale;
};

__interface IMove { //интерфейс передвижения
	void SetPosition(XY xy);
	void ChangePosition(XY xy);
};

__interface IRotate { //интерфейс поворота 
	void SetAngle(Angle angle);
	void ChangeAngle(Angle angle);
};

__interface IDraw { //интерфейс рисования
	void Draw(sf::RenderWindow& window);
};

__interface IScale { //интерфейс масштабирования
	void SetScale(Scale scale);
	void ChangeScale(Scale scale);
};

__interface IColor {
	void SetColor(RGB rgb);
};

__interface IHistory {  //интерфейс ведения истории
	void PreviousCondition();
	void RememberCondition();
};