#pragma once
#include "XY.h"
#include <SFML/Graphics.hpp>

__interface IMove { //��������� ������������
	void SetPosition(float x, float y);
	void SetPosition(XY xy);
};

__interface IRotate { //��������� �������� 
	void SetAngle(float angle);
};

__interface IDraw { //��������� ���������
	void Draw(sf::RenderWindow& window);
};

__interface IScale {
	void SetScale(float percent);
};

__interface IHistory {
	void Previous();
	void Remember();
};