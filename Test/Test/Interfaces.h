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

__interface IShape {  //��������� ������� �������
	virtual void PreviousCondition() abstract;
	virtual void RememberCondition() abstract;
};

__interface IMove : IShape { //��������� ������������
	virtual void SetPosition(XY xy) abstract;
	virtual void ChangePosition(XY xy) abstract;
};

__interface IRotate : IShape { //��������� �������� 
	virtual void SetAngle(Angle angle)  abstract;
	virtual void ChangeAngle(Angle angle) abstract;
};

__interface IDraw : IShape { //��������� ���������
	virtual void Draw(sf::RenderWindow& window) abstract;
	virtual void SetColor(RGB rgb) abstract;
};

__interface IScale : IShape { //��������� ���������������
	virtual void SetScale(Scale scale) abstract;
	virtual void ChangeScale(Scale scale) abstract;
};