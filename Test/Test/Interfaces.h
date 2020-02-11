#pragma once
#include "XY.h"
#include "RGB.h"
#include <SFML/Graphics.hpp>

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
	explicit Scale(float scale) : Scale(scale, scale) {}
	explicit Scale(float scaleX, float scaleY) : scaleX(scaleX), scaleY(scaleY){}
	float GetValueX() const {
		return this->scaleX;
	}
	float GetValueY() const {
		return this->scaleY;
	}
	friend bool operator==(const Scale& first, const Scale& second) {
		return first.GetValueX() == second.GetValueX() && first.GetValueY() == second.GetValueY();
	}
	friend bool operator!=(const Scale& first, const Scale& second) {
		return !(first == second);
	}
protected:
	float scaleX;
	float scaleY;
};

__interface IShape {  //интерфейс ведения истории
	virtual void PreviousCondition() abstract;
	virtual void RememberCondition() abstract;
	virtual void FirstCondition()	 abstract;
};

__interface IMove : IShape { //интерфейс передвижения
	virtual void SetPosition(XY xy) abstract;
	virtual void ChangePosition(XY xy) abstract;
};

__interface IRotate : IShape { //интерфейс поворота 
	virtual void SetAngle(Angle angle)  abstract;
	virtual void ChangeAngle(Angle angle) abstract;
};

__interface IDraw : IShape { //интерфейс рисования
	virtual void Draw(sf::RenderWindow& window) abstract;
	virtual void SetColor(RGB rgb) abstract;
};

__interface IScale : IShape { //интерфейс масштабирования
	virtual void SetScale(Scale scale) abstract;
	virtual void ChangeScale(Scale scale) abstract;
};