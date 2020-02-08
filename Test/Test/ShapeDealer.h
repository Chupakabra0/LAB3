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
	}
	static void SetPosition(IMove* move, XY xy) {
		move->SetPosition(xy);
	}
	static void Rotate(IRotate* rotate, Angle angle) {
		rotate->ChangeAngle(angle);
	}
	static void SetAngle(IRotate* rotate, Angle angle) {
		rotate->SetAngle(angle);
	}
	static void SetColor(IColor* object, RGB color) {
		object->SetColor(color);
	}
	static void Zoom(IScale* object, Scale scale) {
		object->ChangeScale(scale);
	}
	static void SetScale(IScale* object, Scale scale) {
		object->SetScale(scale);
	}
};