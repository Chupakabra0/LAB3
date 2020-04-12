#pragma once
#include "Figure.h"
#include "ShapeDealer.h"

class Triangle : public Figure
{
public:
	Triangle() = delete;
	Triangle(float x, float radius);
	Triangle(float x, float y, float radius);
	Triangle(float x, float y, sf::Color color, float radius);
	Triangle(XY xy, sf::Color color, float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Triangle();
protected:
	void Draw(sf::RenderWindow& window) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Triangle* Copy() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Shape* GetPicture() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::CircleShape pic;
};