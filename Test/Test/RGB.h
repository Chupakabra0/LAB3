#pragma once

class RGB {
public:
	RGB();
	RGB(float color);
	RGB(float red, float green, float blue);
	//---------------------------------------------------------------------
	float getR() const;
	float getG() const;
	float getB() const;
	void setR(float red);
	void setG(float green);
	void setB(float blue);
	void setRGB(float red, float green, float blue);
	//---------------------------------------------------------------------
	friend bool operator==(const RGB& first, const RGB& second);
	friend bool operator!=(const RGB& first, const RGB& second);
	RGB& operator=(RGB& rgb);
	//---------------------------------------------------------------------
	virtual ~RGB();
protected:
	float red;
	float green;
	float blue;
};
