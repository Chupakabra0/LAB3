#include "ShapeDealer.h"
#include "Main.h"

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
void ShapeDealer::DrawPosition(Figure* figure, sf::RenderWindow& window) {
	sf::Text text;
	Main::TextProcedure(text, std::to_string(static_cast<long long>(figure->GetPosition().GetX())) + ";" + std::to_string(static_cast<long long>(figure->GetPosition().GetY())));
	text.setPosition(figure->GetPosition().GetX() * figure->GetScale().GetX() + 10.f, figure->GetPosition().GetY() + 15.f);
	text.setFillColor(figure->GetColor());
	text.setOutlineThickness(1.f);
	text.setOutlineColor(ReverseColor(text.getFillColor()));
	sf::Font font;
	font.loadFromFile("BAUHS93.ttf");
	text.setFont(font);
	window.draw(text);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
float ShapeDealer::CountRadius(Figure* first, Figure* second) {
	return sqrtf(powf(second->GetPosition().GetX() - first->GetPosition().GetX(), 2)
		+
		powf(second->GetPosition().GetY() - first->GetPosition().GetY(), 2));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
sf::Color ShapeDealer::ReverseColor(sf::Color color) {
	return {static_cast<sf::Uint8>(255 - color.r), static_cast<sf::Uint8>(255 - color.g), static_cast<sf::Uint8>(255 - color.b), color.a};
}