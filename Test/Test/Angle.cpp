#include "Angle.h"

Angle::Angle(): Angle(0.f) {}

Angle::Angle(float angle): angle(angle) {
	AngleRot(*this);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
float Angle::GetValue() const {
	return this->angle;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------
void Angle::AngleRot(Angle& angle) {
	while (angle.angle >= 360) {
		angle.angle -= 360;
	}
}