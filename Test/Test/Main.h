#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "ShapeDealer.h"

struct Main {
	static void FileProcedure(std::vector<Figure*>& shapes, std::vector<int>& focus);
	static void TextDisplay(sf::RenderWindow& window, sf::View camera, std::string cmd, bool cmdActive);
	static void TextProcedure(sf::Text& text, std::string string);
	static void Program();
};