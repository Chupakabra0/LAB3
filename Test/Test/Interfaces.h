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

struct IMove //интерфейс передвижения
{
	virtual void ChangePosition(double dx, double dy) abstract;
	virtual void SetPosition(double dx, double dy) abstract;
	virtual void PreviousPosition() abstract;
	virtual ~IMove() = default;
};

class IFocus {
public:
	IFocus() = delete;
	IFocus(bool focus) : focus(focus) {}
	virtual bool getFocus() {
		return this->focus;
	}
	virtual void switchFocus() {
		this->focus = !this->focus;
	}
	virtual void setFocus(bool focus) {
		this->focus = focus;
	}
	virtual ~IFocus() = default;
private:
	bool focus;
};

