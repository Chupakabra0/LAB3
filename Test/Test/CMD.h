#pragma once
#include <string>
#include "Circle.h"
#include "ShapeDealer.h"

using namespace std;
using namespace sf;

enum figureID {
	AGREGAT,
	CIRCLE,
	TRIANGLE,
	DIAMOND,
	STAR
	/*
	 * „тобы добавить новую фигуру, писать сюда новый id
	*/
};

std::string to_string(figureID id);

struct CMD {
	CMD() = delete;
	~CMD() = delete;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	constexpr static float TIME = 2.f;;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static float SPEED;
	static int MOVE;
	static float ROTATE;
	static int SCALE_PLUS;
	static int SCALE_MINUS;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	const static std::string SET;
	const static std::string CHANGE;
	const static std::string CREATE;
	const static std::string WIPE;
	const static std::string SWITCH;
	const static std::string POSITION;
	const static std::string ANGLE;
	const static std::string COLOR;
	const static std::string FOCUS;
	const static std::string SCALE;
	const static std::string DELETE;
	const static std::string VISIBLE;
	const static std::string TRACE;
	const static std::string UP;
	const static std::string DOWN;
	const static std::string ALL;
	const static std::string BD;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	const static std::string SPEED_TEXT;
	const static std::string MOVE_TEXT;
	const static std::string ROTATE_TEXT;
	const static std::string SCALE_TEXT;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	const static std::string X;
	const static std::string Y;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	const static std::string AGREGAT;
	const static std::string CIRCLE;
	const static std::string TRIANGLE;
	const static std::string DIAMOND;
	const static std::string STAR;
	/*
	 * „тобы добавить новую фигуру, писать сюда новую строку-id
	 */
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void Key(std::vector<Figure*>& shapes, Event& event, std::vector<int>& focus, figureID& id);
	static void Text(std::vector<Figure*>& shapes, std::string& string, const Event& event, std::vector<int>& focus);
	static void Check(std::vector<Figure*>& shapes, std::string& string, std::vector<int>& focus);
private:
	static void RememberToFile(std::string string);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void WipeFigure(vector<Figure*> shape, vector<int>& focus);
	static void WipeAllFigure(vector<Figure*>& shape, vector<int>& focus);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static std::vector<int> Convert(std::string& string);
	static std::string NumberCheck(std::string& string);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void CreateFigure(std::vector<Figure*>& shapes, std::vector<int>& coordinates, std::vector<int>& focus, figureID id);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigurePosition(IMove* shape, std::vector<int>& coordinates);
	static void ChangeFigurePosition(IMove* shape, std::vector<int>& coordinates);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureAngle(IRotate* shape, std::vector<int>& coordinates);
	static void ChangeFigureAngle(IRotate* shape, std::vector<int>& coordinates);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureColor(IDraw* shape, std::vector<int>& coordinates);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureScale(IScale* shape, std::vector<int>& coordinates);
	static void ChangeFigureScale(IScale* shape, std::vector<int>& coordinates);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureScaleX(IScale* shape, std::vector<int>& coordinates);
	static void SetFigureScaleY(IScale* shape, std::vector<int>& coordinates);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureFocus(std::vector<Figure*>& shapes, vector<int>& coordinates, std::vector<int>& focus);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void DeleteFigure(std::vector<Figure*>& shapes);
	static void DeleteFigure(std::vector<Figure*>& shapes, std::vector<int>& coordinates, std::vector<int>& focus);
	static void DeleteFigure(std::vector<Figure*>& shapes, std::vector<int>& focus);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureVisible(std::vector<Figure*>& shapes, std::vector<int>& coordinates);
	static void SetFigureVisible(std::vector<Figure*>& shapes, int& focus);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetFigureTrace(std::vector<Figure*>& shapes, vector<int>& coordinates);
	static void SetFigureTrace(std::vector<Figure*>& shapes, int& focus);
	static void SetFigureTrace(std::vector<Figure*>& shapes);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void ConstantSetter(float& value, const float& coordinates);
	static void ConstantSetter(int& value, const float& coordinates);
};