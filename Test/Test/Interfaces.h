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

__interface IMove { //��������� ������������
	void SetPosition(XY xy);
	void ChangePosition(XY xy);
};

__interface IRotate { //��������� �������� 
	void SetAngle(Angle angle);
	void ChangeAngle(Angle angle);
};

__interface IDraw { //��������� ���������
	void Draw(sf::RenderWindow& window);
};

__interface IScale { //��������� ���������������
	void SetScale(Scale scale);
	void ChangeScale(Scale scale);
};

__interface IColor {
	void SetColor(RGB rgb);
};

__interface IHistory {  //��������� ������� �������
	void PreviousCondition();
	void RememberCondition();
};