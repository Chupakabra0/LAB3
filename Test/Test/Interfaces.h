#pragma once
#include <string>

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

std::string to_string(Color color) {
	switch (color) {
	case BLACK: return static_cast<std::string>("Black");
	case BLUE: return static_cast<std::string>("Blue");
	case GREEN: return static_cast<std::string>("Green");
	case CYAN: return static_cast<std::string>("Cyan");
	case RED: return static_cast<std::string>("Red");
	case MAGENTA: return static_cast<std::string>("Magenta");
	case BROWN: return static_cast<std::string>("Brown");
	case LIGHTGRAY: return static_cast<std::string>("Light gray");
	case DARKGRAY: return static_cast<std::string>("Dark gray");
	case LIGHTBLUE: return static_cast<std::string>("Light blue");
	case LIGHTGREEN: return static_cast<std::string>("Light green");
	case LIGHTCYAN: return static_cast<std::string>("Light cyan");
	case LIGHTRED: return static_cast<std::string>("Light red");
	case LIGHTMAGENTA: return static_cast<std::string>("Light magenta");
	case YELLOW: return static_cast<std::string>("Yellow");
	case WHITE: return static_cast<std::string>("White");
	default: return static_cast<std::string>("Unknown");
	}
}

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
protected:
	bool focus;
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
