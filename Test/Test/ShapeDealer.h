#pragma once
#include "Interfaces.h"
#include "Circle.h"

struct ShapeDealer
{
	ShapeDealer() = delete;
	~ShapeDealer() = delete;
	//---------------------------------------------------------------------
	static void Draw(IDraw* draw, sf::RenderWindow& window, std::vector<Figure*>& shapes) {
		draw->Draw(window, shapes);
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
	static void SetColor(IDraw* object, sf::Color color) {
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
	static void SwitchFocus(Figure* figure) {
		figure->setFocus(!figure->getFocus());
	}
	static void SwitchVisible(Figure* figure) {
		figure->setVisible(!figure->getVisible());
	}
	static void SwitchTrace(Figure* figure) {
		figure->setTrace(!figure->getTrace());
		if (figure->getTrace()) figure->setTraceNum(figure->getHistory().size() - 1);
	}	
	static Figure* MakeCopy(Figure* figure) {
		return figure->Copy();
	}
};