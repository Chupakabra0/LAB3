#pragma once
#include "Interfaces.h"

class Scale : public IScale {
public:
	Scale() = default;
	Scale(float scale) : scale(scale) {}
	//---------------------------------------------------------------------
	void SetScale(float percent) override;
	float GetScale() const;
	//---------------------------------------------------------------------
	friend bool operator==(const Scale& first, const Scale& second);
	friend bool operator!=(const Scale& first, const Scale& second);
	//---------------------------------------------------------------------
	virtual ~Scale() = default;
protected:
	float scale;
};