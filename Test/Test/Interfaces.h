#pragma once

struct IMove //интерфейс передвижения
{
	virtual void ChangePosition(double dx, double dy) abstract;
	virtual void SetPosition(double dx, double dy) abstract;
	virtual void PreviousPosition() abstract;
};