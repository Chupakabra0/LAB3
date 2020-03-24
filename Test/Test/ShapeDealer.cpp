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
	figure->SetFocus(!figure->GetFocus());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SwitchVisible(Figure* figure) {
	figure->SetVisible(!figure->GetVisible());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::SwitchTrace(Figure* figure) {
	figure->SetTrace(!figure->GetTrace());
	if (figure->GetTrace()) figure->SetTraceNum(figure->GetHistory().size() - 1);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* ShapeDealer::MakeCopy(Figure* figure) {
	return figure->Copy();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void ShapeDealer::ObstacleScale(std::vector<Figure*>& shapes, int index) {
	for (auto i = 0; i < shapes.size(); i++) {
		if (i != index) {
			if (CountRadius(shapes[index], shapes[i]) <= shapes[index]->GetRadius() + shapes[i]->GetRadius()) {
				shapes[index]->SetTouch(true);
			}
			else if (shapes[index]->GetTouch()) {
				shapes[index]->SetTouch(false);
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