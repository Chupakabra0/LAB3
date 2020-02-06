#pragma once
#include "Interfaces.h"
#include <utility>
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
	Dot GetDot() const {
		return this->dot;
	}
	Scale GetScale() const {
		return this->scale;
	}
	Angle GetAngle() const {
		return this->angle;
	}
	RGB GetColor() const {
		return this->color;
	}
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
	void SetScale(const Scale& scale) {
		this->scale.SetScale(scale.GetScale());
		this->Remember();
	}
	void SetAngle(const Angle& angle) {
		this->angle.SetAngle(angle.GetAngle());
		this->Remember();
	}
	void SetDot(const Dot& dot) {
		this->dot.SetPosition(dot.GetPosition());
		this->Remember();
	}
	void SetColor(const RGB& color) {
		this->color.setRGB(color.getR(), color.getG(), color.getB());
		this->Remember();
	}
	//---------------------------------------------------------------------
	virtual ~Point();
protected:
	void Remember();
	Scale scale;
	Angle angle;
	Dot dot;
	RGB color;
	std::vector<History> history;
};