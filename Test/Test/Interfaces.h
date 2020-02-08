#pragma once
#include "XY.h"
#include "RGB.h"
#include <SFML/Graphics.hpp>

__interface IMove { //интерфейс передвижения
	void SetPosition(float x);
	void SetPosition(float x, float y);
	void SetPosition(XY xy);
	void ChangePosition(float xy);
	void ChangePosition(float x, float y);
	void ChangePosition(XY xy);
};

__interface IRotate { //интерфейс поворота 
	void SetAngle(float angle);
	void ChangeAngle(float angle);
};

__interface IDraw { //интерфейс рисования
	void Draw(sf::RenderWindow& window);
};

__interface IScale { //интерфейс масштабирования
	void SetScale(float scale);
	void ChangeScale(float scale);
};

__interface IColor {
	void SetColor(float red, float green, float blue);
	void SetColor(RGB rgb);
};

__interface IHistory {  //интерфейс ведения истории
	void PreviousCondition();
	void RememberCondition();
};