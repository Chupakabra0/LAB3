#pragma once
#include "XY.h"
#include <SFML/Graphics.hpp>

__interface IMove { //интерфейс передвижения
	void SetPosition(float x, float y);
	void SetPosition(XY xy);
};

__interface IRotate { //интерфейс поворота 
	void SetAngle(float angle);
};

__interface IDraw { //интерфейс рисования
	void Draw(sf::RenderWindow& window);
};

__interface IScale { //интерфейс масштабирования
	void SetScale(float percent);
};

__interface IHistory {  //интерфейс ведения истории
	void PreviousCondition();
	void RememberCondition();
};