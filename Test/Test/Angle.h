#pragma once

class Angle {
public:
	explicit Angle();
	explicit Angle(float angle);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	float GetValue() const;
protected:
	static void AngleRot(Angle& angle);
	float angle;
};