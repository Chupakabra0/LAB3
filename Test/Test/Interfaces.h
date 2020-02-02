#pragma once

enum Color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

class XY {
public:
	XY() = default;
	XY(float x) : XY(x, x) {}
	XY(float x, float y) : x(x), y(y) {}
	virtual float getX() const {
		return this->x;
	}
	virtual float getY() const {
		return this->y;
	}
	virtual void setX(float x) {
		this->x = x;
	}
	virtual void setY(float y) {
		this->y = y;
	}
	virtual void setXY(float x, float y) {
		this->setX(x);
		this->setY(y);
	}
	virtual void setXY(XY dxdy) {
		this->setXY(dxdy.getX(), dxdy.getY());
	}
	virtual void changeX(float dx) {
		this->x += dx;
	}
	virtual void changeY(float dy) {
		this->y += dy;
	}
	virtual void changeXY(float dx, float dy) {
		this->changeX(dx);
		this->changeY(dy);
	}
	virtual void changeXY(XY dxdy) {
		this->changeXY(dxdy.getX(), dxdy.getY());
	}
protected:
	float x;
	float y;
};

struct IMove //интерфейс передвижения
{
	virtual void ChangePosition(float dx, float dy) abstract;
	virtual void SetPosition(float x, float y) abstract;
	virtual void ChangePosition(XY xy) abstract;
	virtual void SetPosition(XY xy) abstract;
	virtual void RememberPosition(float x, float y) abstract;
	virtual void RememberPosition(XY xy) abstract;
	virtual void PreviousPosition() abstract;
	virtual ~IMove() = default;
};

struct IDraw {
	virtual void Draw() abstract;
};

class IColor {
public:
	IColor() = delete;
	IColor(Color color) : color(color) {}
	virtual Color getColor() {
		return this->color;
	}
	virtual void setColor(Color color) {
		this->color = color;
	}
	virtual ~IColor() = default;
protected:
	Color color;
};