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

	constexpr static float TIME = 2.f;;

	static float SPEED;
	static float MOVE;
	static float ROTATE;
	static float SCALE_PLUS;
	static float SCALE_MINUS;

	const static std::string SET;
	const static std::string CREATE;
	const static std::string SWITCH;
	const static std::string POSITION;
	const static std::string ANGLE;
	const static std::string COLOR;
	const static std::string FOCUS;
	const static std::string SCALE;
	const static std::string DELETE;
	const static std::string VISIBLE;
	const static std::string TRACE;
	const static std::string ALL;

	const static std::string SPEED_TEXT;
	const static std::string MOVE_TEXT;
	const static std::string ROTATE_TEXT;
	const static std::string SCALE_TEXT;


	const static std::string X;
	const static std::string Y;

	const static std::string CIRCLE;

	static void Key(std::vector<Figure*>& shapes, Event& event, unsigned int& focus, figureID& id);
	static void Text(std::vector<Figure*>& shapes, std::string& string, const Event& event, unsigned int& focus, figureID& id);
private:
	static void Check(std::vector<Figure*>& shapes, std::string& string, unsigned int& focus, figureID& id);
	static std::vector<float> Convert(std::string& string);
	static std::string NumberCheck(std::string& string);

	static void CreateFigure(std::vector<Figure*>& shapes, std::vector<float>& coordinates, unsigned int& focus, figureID& id);

	static void SetFigurePosition(IMove* shape, std::vector<float>& coordinates);

	static void SetFigureAngle(IRotate* shape, std::vector<float>& coordinates);

	static void SetFigureColor(IDraw* shape, std::vector<float>& coordinates);

	static void SetFigureScale(IScale* shape, std::vector<float>& coordinates);
	static void SetFigureScaleX(IScale* shape, std::vector<float>& coordinates);
	static void SetFigureScaleY(IScale* shape, std::vector<float>& coordinates);

	static void SetFigureFocus(std::vector<Figure*>& shapes, vector<float>& coordinates, unsigned& focus);

	static void DeleteFigure(std::vector<Figure*>& shapes);
	static void DeleteFigure(std::vector<Figure*>& shapes, vector<float>& coordinates, unsigned& focus);
	static void DeleteFigure(std::vector<Figure*>& shapes, unsigned& focus);

	static void SetFigureVisible(std::vector<Figure*>& shapes, vector<float>& coordinates);
	static void SetFigureVisible(std::vector<Figure*>& shapes, unsigned& focus);

	static void SetFigureTrace(std::vector<Figure*>& shapes, vector<float>& coordinates);
	static void SetFigureTrace(std::vector<Figure*>& shapes, unsigned& focus);
	static void SetFigureTrace(std::vector<Figure*>& shapes);

	static void ConstantSetter(float& value, const float& coordinates);
};