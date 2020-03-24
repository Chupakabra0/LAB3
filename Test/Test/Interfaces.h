#pragma once
#include <SFML/Graphics.hpp>

#include "XY.h"
#include "Scale.h"

struct IShape {  //интерфейс ведения истории
	virtual void PreviousCondition() abstract;
	virtual void RememberCondition() abstract;
	virtual void FirstCondition() abstract;
};

struct IMove : virtual IShape { //интерфейс передвижения
	virtual XY GetPosition() abstract;
	virtual void SetPosition(XY xy) abstract;
	virtual void ChangePosition(XY xy) abstract;
};

struct IRotate : virtual IShape { //интерфейс поворота 
	virtual void SetAngle(Angle angle) abstract;
	virtual void ChangeAngle(Angle angle) abstract;
};

struct IDraw : virtual IShape { //интерфейс рисования
	virtual void Draw(sf::RenderWindow& window) abstract;
	virtual void SetColor(sf::Color rgba) abstract;
};

struct IScale : virtual IShape { //интерфейс масштабирования
	virtual void SetScale(Scale scale) abstract;
	virtual void ChangeScale(Scale scale) abstract;
};