#pragma once																 
#include "Interfaces.h"														 
#include <vector>															 														 
#include "History.h"

struct Figure : IMove, IScale, IDraw, IRotate {
	Figure() : indexTrace(0), indexRecord(0) {
		this->setFocus(false);
		this->setTrace(false);
		this->setVisible(true);
		this->setRecord(false);
	}
	virtual ~Figure() = default;

	bool getFocus() const {
		return this->isFocused;
	}
	void setFocus(bool focus) {
		set(this->isFocused, focus);
	}

	bool getVisible() const {
		return this->isVisible;
	}
	void setVisible(bool visible) {
		set(this->isVisible, visible);
	}

	bool getTrace() const {
		return this->isTraced;
	}
	void setTrace(bool trace) {
		set(this->isTraced, trace);
	}

	bool getRecord() const {
		return this->indexRecord;
	}
	void setRecord(bool record) {
		set(this->isRecord, record);
	}

	size_t getTraceNum() const {
		return this->indexTrace;
	}
	void setTraceNum(size_t trace) {
		this->indexTrace = trace;
	}

	size_t getRecordNum() const {
		return this->indexRecord;
	}
	void setRecordNum(size_t record) {
		this->indexRecord = record;
	}

	std::vector<History> getHistory() const {
		return this->history;
	}
protected:
	bool isFocused;
	bool isVisible;
	bool isTraced;
	bool isRecord;
	size_t indexTrace;
	size_t indexRecord;
	std::vector<History> history;
private:
	static void set(bool& first, const bool& second) {
		if (first != second) first = second;
	}
};

class Circle : public Figure
{
public:
	Circle() = delete;
	Circle(float x, float radius);
	Circle(float x, float y, float radius);
	Circle(float x, float y, sf::Color color, float radius);
	Circle(XY xy, sf::Color color, float radius);
	virtual ~Circle();
protected:
	void Draw(sf::RenderWindow& window) override;
	//---------------------------------------------------------------------
	void SetPosition(XY xy) override;
	void ChangePosition(XY xy) override;
	//---------------------------------------------------------------------
	void SetScale(Scale scale) override;
	void ChangeScale(Scale scale) override;
	//---------------------------------------------------------------------
	void SetColor(sf::Color rgb) override;
	//---------------------------------------------------------------------
	void SetAngle(Angle angle) override {
		this->angle = angle;
	}
	void ChangeAngle(Angle angle) override {
		this->SetAngle(Angle(this->angle.GetValue() + angle.GetValue()));
	}
	//---------------------------------------------------------------------
	void PreviousCondition() override;
	void RememberCondition() override;
	void FirstCondition() override;
	//---------------------------------------------------------------------
	Scale scale;
	Angle angle;
	XY dot;
	float radius;
	sf::Color color;
};