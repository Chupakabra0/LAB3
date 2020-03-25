#pragma once
#include "Interfaces.h"
#include "Circle.h"

struct ShapeDealer {
	ShapeDealer() = delete;
	~ShapeDealer() = delete;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void Draw(IDraw* draw, sf::RenderWindow& window);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void Move(IMove* move, XY xy);
	static void SetPosition(IMove* move, XY xy);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void Rotate(IRotate* rotate, Angle angle);
	static void SetAngle(IRotate* rotate, Angle angle);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SetColor(IDraw* object, sf::Color color);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void Zoom(IScale* object, Scale scale);
	static void SetScale(IScale* object, Scale scale);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void LegacyCondition(IHistory* shape);
	static void FirstCondition(IHistory* shape);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void SwitchFocus(Figure* figure);
	static void SwitchVisible(Figure* figure);
	static void SwitchTrace(Figure* figure);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static Figure* MakeCopy(Figure* figure);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static void ObstacleScale(std::vector<Figure*>& shapes, int index);
	static void DrawPosition(Figure* figure, sf::RenderWindow& window);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	static sf::Color ReverseColor(sf::Color color);
private:
	static float CountRadius(Figure* first, Figure* second);
};