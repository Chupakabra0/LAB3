#pragma once
#include "XY.h"
#include <SFML/Graphics.hpp>

class Figure;

class Angle {
public:
	explicit Angle() = default;
	explicit Angle(float angle): angle(angle) {
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
	explicit Scale() = default;
	explicit Scale(float scale) : Scale(XY(scale)) {}
	explicit Scale(XY scale) : scale(scale) {}
	float GetValueX() const {
		return this->scale.getX();
	}
	float GetValueY() const {
		return this->scale.getY();
	}
	friend bool operator==(const Scale& first, const Scale& second) {
		return first.getPoint() == second.getPoint();
	}
	friend bool operator!=(const Scale& first, const Scale& second) {
		return !(first == second);
	}
protected:
	XY scale;
	XY getPoint() const {
		return this->scale;
	}
};

__interface IShape {  //интерфейс ведения истории
	void PreviousCondition();
	void RememberCondition();
	void FirstCondition();
};

__interface IMove : IShape { //интерфейс передвижения
	XY GetPosition();
	void SetPosition(XY xy);
	void ChangePosition(XY xy);
};

__interface IRotate : IShape { //интерфейс поворота 
	void SetAngle(Angle angle);
	void ChangeAngle(Angle angle);
};

__interface IDraw : IShape { //интерфейс рисования
	void Draw(sf::RenderWindow& window, std::vector<Figure*>& shapes);
	void SetColor(sf::Color rgba);
};

__interface IScale : IShape { //интерфейс масштабирования
	void SetScale(Scale scale);
	void ChangeScale(Scale scale);
};