#pragma once
#include "XY.h"
#include "RGB.h"
#include <SFML/Graphics.hpp>

__interface IMove { //��������� ������������
	void SetPosition(float x);
	void SetPosition(float x, float y);
	void SetPosition(XY xy);
	void ChangePosition(float xy);
	void ChangePosition(float x, float y);
	void ChangePosition(XY xy);
};

__interface IRotate { //��������� �������� 
	void SetAngle(float angle);
	void ChangeAngle(float angle);
};

__interface IDraw { //��������� ���������
	void Draw(sf::RenderWindow& window);
};

__interface IScale { //��������� ���������������
	void SetScale(float scale);
	void ChangeScale(float scale);
};

__interface IColor {
	void SetColor(float red, float green, float blue);
	void SetColor(RGB rgb);
};

__interface IHistory {  //��������� ������� �������
	void PreviousCondition();
	void RememberCondition();
};