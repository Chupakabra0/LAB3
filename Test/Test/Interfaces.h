#pragma once
#include <GLFW/glfw3.h>
#include "XY.h"

__interface IMove { //интерфейс передвижения
	virtual void SetPosition(float x, float y) abstract;
	virtual void SetPosition(XY xy) abstract;
};

__interface IRotate { //интерфейс поворота 
	virtual void SetAngle(float angle) abstract;
};

__interface IDraw { //интерфейс рисования
	virtual void Draw() abstract;
};

__interface IScale {
	virtual void ChangeScale(float percent) abstract;
	virtual void SetScale(float percent) abstract;
};