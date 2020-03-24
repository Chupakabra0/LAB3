#include "ShapeDealer.h"

void ShapeDealer::Draw(IDraw* draw, sf::RenderWindow& window) {
	draw->Draw(window);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::Move(IMove* move, XY xy) {
	move->ChangePosition(xy);
	move->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SetPosition(IMove* move, XY xy) {
	move->SetPosition(xy);
	move->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::Rotate(IRotate* rotate, Angle angle) {
	rotate->ChangeAngle(angle);
	rotate->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SetAngle(IRotate* rotate, Angle angle) {
	rotate->SetAngle(angle);
	rotate->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SetColor(IDraw* object, sf::Color color) {
	object->SetColor(color);
	object->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::Zoom(IScale* object, Scale scale) {
	object->ChangeScale(scale);
	object->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SetScale(IScale* object, Scale scale) {
	object->SetScale(scale);
	object->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::LegacyCondition(IHistory* shape) {
	shape->PreviousCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::FirstCondition(IHistory* shape) {
	shape->FirstCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SwitchFocus(Figure* figure) {
	figure->setFocus(!figure->getFocus());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SwitchVisible(Figure* figure) {
	figure->setVisible(!figure->getVisible());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SwitchTrace(Figure* figure) {
	figure->setTrace(!figure->getTrace());
	if (figure->getTrace()) figure->setTraceNum(figure->getHistory().size() - 1);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* ShapeDealer::MakeCopy(Figure* figure) {
	return figure->Copy();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::ObstacleScale(std::vector<Figure*>& shapes, int index) {
	for (auto i = 0; i < shapes.size(); i++) {
		if (i != index) {
			if (CountRadius(shapes[index], shapes[i]) <= shapes[index]->getRadius() + shapes[i]->getRadius()) {
				shapes[index]->setTouch(true);
			}
			else if (shapes[index]->getTouch()) {
				shapes[index]->setTouch(false);
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
float ShapeDealer::CountRadius(Figure* first, Figure* second) {
	return sqrtf(powf(second->GetPosition().getX() - first->GetPosition().getX(), 2)
		+
		powf(second->GetPosition().getY() - first->GetPosition().getY(), 2));
}