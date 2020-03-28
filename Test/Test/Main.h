#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "CMD.h"

struct Main {
	static void FileProcedure(std::vector<Figure*>& shapes, std::vector<int>& focus);
	static void TextDisplay(sf::RenderWindow& window, sf::View camera, std::string cmd, bool cmdActive, figureID id);
	static void TextProcedure(Text& text, sf::String string);
	static void Program();

	static void Tip(RenderWindow& window, View& camera) {
		
		ifstream file("instructions.txt");
		std::string instructions;
		if (!file.is_open()) {
			instructions = "Error";
		}
		else {
			Text text;
			Font font;
			font.loadFromFile("MKARCADECAPS.ttf");
			text.setFont(font);
			text.setFillColor(Color::White);
			for (auto i = 0; !file.eof(); i += text.getCharacterSize()) {
				getline(file, instructions);
				text.setString(instructions);
				text.setPosition(camera.getCenter().x - 960.f, camera.getCenter().y - 540.f + i);
				window.draw(text);
			}
		}
		file.close();
	}
};
