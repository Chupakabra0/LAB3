#pragma once

#include "Interfaces.h"														 
#include "History.h"
#include "Figure.h"

class Diamond : public Figure
{
public:
	Diamond() = delete;
	Diamond(float x, float radius);
	Diamond(float x, float y, float radius);
	Diamond(float x, float y, sf::Color color, float radius);
	Diamond(XY xy, sf::Color color, float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Diamond();
private:
	void Draw(sf::RenderWindow& window) override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	Diamond* Copy() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::Shape* GetPicture() override;
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	sf::CircleShape pic;
};
