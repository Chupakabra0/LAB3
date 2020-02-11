#pragma once
#include "Interfaces.h"

struct ShapeDealer
{
	ShapeDealer() = delete;
	~ShapeDealer() = delete;
	//---------------------------------------------------------------------
	static void Draw(IDraw* draw, sf::RenderWindow& window) {
		draw->Draw(window);
	}
	static void Move(IMove* move, XY xy) {
		move->ChangePosition(xy);
		move->RememberCondition();
	}
	static void SetPosition(IMove* move, XY xy) {
		move->SetPosition(xy);
		move->RememberCondition();
	}
	static void Rotate(IRotate* rotate, Angle angle) {
		rotate->ChangeAngle(angle);
		rotate->RememberCondition();
	}
	static void SetAngle(IRotate* rotate, Angle angle) {
		rotate->SetAngle(angle);
		rotate->RememberCondition();
	}
	static void SetColor(IDraw* object, RGB color) {
		object->SetColor(color);
		object->RememberCondition();
	}
	static void Zoom(IScale* object, Scale scale) {
		object->ChangeScale(scale);
		object->RememberCondition();
	}
	static void SetScale(IScale* object, Scale scale) {
		object->SetScale(scale);
		object->RememberCondition();
	}
	static void LegacyCondition(IShape* shape) {
		shape->PreviousCondition();
	}
	static void FirstCondition(IShape* shape) {
		shape->FirstCondition();
	}
};