#pragma once

struct IMove //��������� ������������
{
	virtual void ChangePosition(double dx, double dy) abstract;
	virtual void SetPosition(double dx, double dy) abstract;
	virtual void PreviousPosition() abstract;
};