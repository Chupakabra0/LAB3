#include "Dot.h"
#include "History.h"

Dot History::GetDot() const { return this->dot; }

Scale History::GetScale() const { return this->scale; }

Angle History::GetAngle() const { return this->angle; }

RGB History::GetColor() const { return this->color; }