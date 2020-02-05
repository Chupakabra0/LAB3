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
	virtual ~RGB();
protected:
	float red{};
	float green{};
	float blue{};
};
