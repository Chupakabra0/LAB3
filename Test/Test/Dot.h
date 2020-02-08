#pragma once
#include "XY.h"
#include "Interfaces.h"

class Dot : public IMove {
public:
	Dot() = default;
	Dot(float x, float y) : Dot(XY(x, y)) {}
	Dot(XY dot) : dot(dot) {}
	//---------------------------------------------------------------------	 
	void SetPosition(float x, float y) override;
	void SetPosition(XY xy) override;
	XY GetPosition() const;
	//---------------------------------------------------------------------	 
	friend bool operator==(const Dot& first, const Dot& second);
	friend bool operator!=(const Dot& first, const Dot& second);
	//---------------------------------------------------------------------
	virtual ~Dot() = default;
protected:
	XY dot;
};
