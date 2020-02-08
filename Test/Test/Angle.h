#pragma once
#include "Interfaces.h"

class Angle : public IRotate {
public:
	Angle() = default;
	Angle(float angle) : angle(angle) {}
	//---------------------------------------------------------------------	 
	void SetAngle(float angle) override;
	float GetAngle() const;
	//---------------------------------------------------------------------	 
	friend bool operator==(const Angle& first, const Angle& second);
	friend bool operator!=(const Angle& first, const Angle& second);
	//---------------------------------------------------------------------	 
	virtual ~Angle() = default;
protected:
	float angle;
};