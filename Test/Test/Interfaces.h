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

struct IShape {  //��������� ������� �������
	virtual void PreviousCondition() abstract;
	virtual void RememberCondition() abstract;
	virtual void FirstCondition() abstract;
};

struct IMove : virtual IShape { //��������� ������������
	virtual XY GetPosition() abstract;
	virtual void SetPosition(XY xy) abstract;
	virtual void ChangePosition(XY xy) abstract;
};

struct IRotate : virtual IShape { //��������� �������� 
	virtual void SetAngle(Angle angle) abstract;
	virtual void ChangeAngle(Angle angle) abstract;
};

struct IDraw : virtual IShape { //��������� ���������
	virtual void Draw(sf::RenderWindow& window, std::vector<Figure*>& shapes) abstract;
	virtual void SetColor(sf::Color rgba) abstract;
};

struct IScale : virtual IShape { //��������� ���������������
	virtual void SetScale(Scale scale) abstract;
	virtual void ChangeScale(Scale scale) abstract;
};