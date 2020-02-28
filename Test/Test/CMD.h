#pragma once
#include <string>
#include "Circle.h"
#include "ShapeDealer.h"

using namespace std;
using namespace sf;

enum figureID {
	CIRCLE
};

std::string to_string(figureID id);

struct CMD {
	CMD() = delete;
	~CMD() = delete;

	static float SPEED;
	static float TIME;
	static float MOVE;
	static float ROTATE;
	static float SCALE_PLUS;
	static float SCALE_MINUS;

	const static std::string SET;
	const static std::string CREATE;
	const static std::string POSITION;
	const static std::string ANGLE;
	const static std::string COLOR;
	const static std::string FOCUS;
	const static std::string SCALE;

	const static std::string X;
	const static std::string Y;

	const static std::string CIRCLE;

	static void Key(std::vector<IShape*>& shapes, Event& event, unsigned int& focus, figureID& id);
	static void Text(std::vector<IShape*>& shapes, std::string& string, const Event& event, unsigned int& focus,
					figureID& id);
private:
	static void Check(std::vector<IShape*>& shapes, std::string& string, unsigned int& focus, figureID& id);
	static std::vector<float> Convert(std::string& string);

	static std::string NumberCheck(std::string& string);
	static void CreateFigure(std::vector<IShape*>& shapes, std::vector<float>& coordinates, unsigned int& focus,
							figureID& id);
	static void SetFigurePosition(IMove* shape, std::vector<float>& coordinates);
	static void SetFigureAngle(IRotate* shape, std::vector<float>& coordinates);
	static void SetFigureColor(IDraw* shape, std::vector<float>& coordinates);
	static void SetFigureScale(IScale* shape, std::vector<float>& coordinates);
	static void SetFigureScaleX(IScale* shape, std::vector<float>& coordinates);
	static void SetFigureScaleY(IScale* shape, std::vector<float>& coordinates);
	static void SetFigureFocus(std::vector<IShape*>& shapes, unsigned& focus, vector<float>& coordinates);
};