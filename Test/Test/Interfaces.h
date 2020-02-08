#pragma once
#include "XY.h"
#include <SFML/Graphics.hpp>

__interface IMove { //��������� ������������
	virtual void SetPosition(float x, float y) abstract;
	virtual void SetPosition(XY xy) abstract;
};

__interface IRotate { //��������� �������� 
	virtual void SetAngle(float angle) abstract;
};

__interface IDraw { //��������� ���������
	virtual void Draw(sf::RenderWindow& window) abstract;
};

__interface IScale {
	virtual void SetScale(float percent) abstract;
};