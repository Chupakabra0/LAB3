#pragma once

class RGB {
public:
	RGB();
	RGB(float color);
	RGB(float red, float green, float blue);

	float getR() const;
	float getG() const;
	float getB() const;
	void setR(float red);
	void setG(float green);
	void setB(float blue);
	void setRGB(float red, float green, float blue);
	//---------------------------------------------------------------------
	friend bool operator==(const RGB& first, const RGB& second) {
		return first.getB() == second.getB() && first.getG() == second.getG() && first.getR() == second.getR();
	}
	friend bool operator!=(const RGB& first, const RGB& second) {
		return !(first == second);
	}
	//---------------------------------------------------------------------
	virtual ~RGB();
protected:
	float red{};
	float green{};
	float blue{};
};
