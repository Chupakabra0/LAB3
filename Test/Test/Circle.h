#pragma once																 
#include <vector>

#include "Interfaces.h"														 
#include "History.h"
#include "Figure.h"

class Circle : public Figure {
public:
	Circle() = delete;
	Circle(float x, float radius);
	Circle(float x, float y, float radius);
	Circle(float x, float y, sf::Color color, float radius);
	Circle(XY xy, sf::Color color, float radius);
	//-----------------------------------------------------------------------------------------------------------------------------------------------
	virtual ~Circle();
protected:
	void Draw(sf::RenderWindow& window) override;
	//---------------------------------------------------------------------
	sf::Shape* GetPicture() override;
	//---------------------------------------------------------------------
	Figure* Copy() override;
	//---------------------------------------------------------------------
	sf::CircleShape pic;
};