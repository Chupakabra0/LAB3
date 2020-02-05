#pragma once
#include <GLFW/glfw3.h>
#include "XY.h"

__interface IMove { //интерфейс передвижения
	virtual void ChangePosition(float dx, float dy) abstract;
	virtual void SetPosition(float x, float y) abstract;
	virtual void ChangePosition(XY xy) abstract;
	virtual void SetPosition(XY xy) abstract;
	virtual void RememberPosition(float x, float y) abstract;
	virtual void RememberPosition(XY xy) abstract;
	virtual void PreviousPosition() abstract;
};

__interface IRotate { //интерфейс поворота 
	virtual void ChangeAngle(float angle) abstract;
	virtual void SetAngle(float angle) abstract;
	virtual void RememberAngle(float angle) abstract;
	virtual void PreviousAngle() abstract;
};

__interface IDraw { //интерфейс рисования
	virtual void Draw() abstract;
};

__interface IScale {
	virtual void ChangeScale(float percent) abstract;
	virtual void SetScale(float percent) abstract;
	virtual void RememberScale(float percent) abstract;
	virtual void PreviousScale() abstract;
};