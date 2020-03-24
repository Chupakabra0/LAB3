#include "Agregat.h"

#include "ShapeDealer.h"

Agregat::Agregat(const Agregat& copy): Agregat(copy.GetFigures()) {}

Agregat::Agregat(std::vector<Figure*> figures): figures(std::move(figures)) {
	this->CenterPos();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::Draw(sf::RenderWindow& window) {
	for (auto& element : this->figures) {
		if (this->isFocused && !element->GetFocus()) ShapeDealer::SwitchFocus(element);
		else if (!this->isFocused && element->GetFocus()) ShapeDealer::SwitchFocus(element);
		element->Draw(window);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
XY Agregat::GetPosition() {
	return this->dot;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::SetPosition(XY xy) {
	for (auto& element : this->figures) {
		element->SetPosition(xy);
	}
	this->CenterPos();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::ChangePosition(XY xy) {
	for (auto& element : this->figures) {
		element->ChangePosition(xy);
	}
	this->CenterPos();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Scale Agregat::GetScale() {
	return this->scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::SetScale(Scale scale) {
	for (auto& element : this->figures) {
		element->SetScale(scale);
	}
	this->scale = scale;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::ChangeScale(Scale scale) {
	for (auto& element : this->figures) {
		element->ChangeScale(scale);
	}
	this->scale = Scale(XY(this->scale.GetValueX() + scale.GetValueX(), this->scale.GetValueY() + scale.GetValueY()));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Angle Agregat::GetAngle() {
	return this->angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::SetAngle(Angle angle) {
	for (auto& element : this->figures) {
		element->SetAngle(angle);
	}
	this->angle = angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::ChangeAngle(Angle angle) {
	for (auto& element : this->figures) {
		element->ChangeAngle(angle);
	}
	this->angle = Angle(this->angle.GetValue() + angle.GetValue());
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::PreviousCondition() {
	for (auto& element : this->figures) {
		element->PreviousCondition();
	}
	if (this->history.size() > 1) {
		this->history.pop_back();
		const auto size = this->history.size() - 1;
		if (this->dot != this->history[size].GetDot()) this->SetPosition(this->history[size].GetDot());
		if (this->scale != this->history[size].GetScale()) this->SetScale(this->history[size].GetScale());
		if (this->color != this->history[size].GetColor()) this->SetColor(this->history[size].GetColor());
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::RememberCondition() {
	for (auto& element : this->figures) {
		element->RememberCondition();
	}
	this->history.emplace_back(History(this->dot, this->scale, this->angle, this->color));
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::FirstCondition() {
	for (auto& element : this->figures) {
		element->FirstCondition();
	}
	if (this->dot != this->history[0].GetDot()) this->SetPosition(this->history[0].GetDot());
	if (this->scale != this->history[0].GetScale()) this->SetScale(this->history[0].GetScale());
	if (this->color != this->history[0].GetColor()) this->SetColor(this->history[0].GetColor());
	this->history.clear();
	this->RememberCondition();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::SetColor(sf::Color rgba) {
	for (auto& element : this->figures) {
		element->SetColor(rgba);
	}
	this->color = rgba;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Figure* Agregat::Copy() {
	return new Agregat(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
std::vector<Figure*> Agregat::GetFigures() const {
	std::vector<Figure*> temp;
	for (auto element : this->figures) {
		temp.push_back(ShapeDealer::MakeCopy(element));
	}
	return temp;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Agregat::CenterPos() {
	this->dot = XY(0.f, 0.f);
	for (auto element : this->figures) {
		this->dot += element->GetPosition();
	}
	if (!this->figures.empty()) this->dot /= this->figures.size();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
Agregat::~Agregat() = default;