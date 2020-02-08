#pragma once
#include "Interfaces.h"
#include <vector>
#include "RGB.h"

class Scale : public IScale {
public:
	Scale() = default;
	Scale(float scale) : scale(scale) {}
	//---------------------------------------------------------------------
	void ChangeScale(float percent) override;
	void SetScale(float percent) override;
	float GetScale() const;
	//---------------------------------------------------------------------
	friend bool operator==(const Scale& first, const Scale& second) {
		return first.GetScale() == second.GetScale();
	}
	friend bool operator!=(const Scale& first, const Scale& second) {
		return !(first == second);
	}
	//---------------------------------------------------------------------
	virtual ~Scale() = default;
protected:
	float scale;
};

class Angle : public IRotate {
public:
	Angle() = default;
	Angle(float angle) : angle(angle) {}
	//---------------------------------------------------------------------
	void SetAngle(float angle) override;
	float GetAngle() const;
	//---------------------------------------------------------------------
	friend bool operator==(const Angle& first, const Angle& second) {
		return first.GetAngle() == second.GetAngle();
	}
	friend bool operator!=(const Angle& first, const Angle& second) {
		return !(first == second);
	}
	//---------------------------------------------------------------------
	virtual ~Angle() = default;
protected:
	float angle;
};

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
	friend bool operator==(const Dot& first, const Dot& second) {
		return first.GetPosition() == second.GetPosition();
	}
	friend bool operator!=(const Dot& first, const Dot& second) {
		return !(first == second);
	}
	//---------------------------------------------------------------------
	virtual ~Dot() = default;
protected:
	XY dot;
};


class History {
public:
	History() = delete;
	explicit History(Dot dot, Scale scale, Angle angle, RGB color) : dot(dot), scale(scale), angle(angle), color(color) {}
	//---------------------------------------------------------------------
	Dot GetDot() const;
	Scale GetScale() const;
	Angle GetAngle() const;
	RGB GetColor() const;
protected:
	Dot dot;
	Scale scale;
	Angle angle;
	RGB color;
};

class Point : public IDraw
{
public:
	Point() = delete;
	Point(float x);
	Point(float x, float y);
	Point(float x, float y, RGB color);
	Point(XY xy, RGB color);
	//---------------------------------------------------------------------
	void Draw() override;
	//---------------------------------------------------------------------
	void Previous();
	//---------------------------------------------------------------------
	Scale GetScale() const;
	Angle GetAngle() const;
	Dot GetDot() const;
	RGB GetColor() const;
	//---------------------------------------------------------------------
	void SetScale(const Scale& scale);
	void SetAngle(const Angle& angle);
	void SetDot(const Dot& dot);
	void SetColor(const RGB& color);
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void SetScaleWithoutR(const Scale& scale);
	void SetAngleWithoutR(const Angle& angle);
	void SetDotWithoutR(const Dot& dot);
	void SetColorWithoutR(const RGB& color);
	//---------------------------------------------------------------------
	void Remember();
	//---------------------------------------------------------------------
	Scale scale;
	Angle angle;
	Dot dot;
	RGB color;
	std::vector<History> history;
};