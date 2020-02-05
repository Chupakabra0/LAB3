#pragma once
#include <GLFW/glfw3.h>

__interface IMove //интерфейс передвижения
{
	virtual void ChangePosition(float dx, float dy) abstract;
	virtual void SetPosition(float x, float y) abstract;
	virtual void ChangePosition(XY xy) abstract;
	virtual void SetPosition(XY xy) abstract;
	virtual void RememberPosition(float x, float y) abstract;
	virtual void RememberPosition(XY xy) abstract;
	virtual void PreviousPosition() abstract;
};

__interface  IDraw {
	virtual void Draw() abstract;
};