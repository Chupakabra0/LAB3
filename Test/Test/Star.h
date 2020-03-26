#pragma once

#include "Figure.h"
#include "ShapeDealer.h"

class Star : public Figure
{
public:
	Star() = delete;
	Star(float x, float radius);
	Star(float x, float y, float radius);
	Star(float x, float y, sf::Color color, float radius);
	Star(XY xy, sf::Color color, float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Star() ;
private:
	void Draw(sf::RenderWindow& window) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Figure* Copy() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::ConvexShape GetPicture() const;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::ConvexShape pic;
};
