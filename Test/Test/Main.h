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

	static void DrawProccess(RenderWindow& window, vector<Figure*>& shapes, vector<int>& focus, bool coordinateActive) {
		for (auto i = 0; i < shapes.size(); i++) {
			ShapeDealer::ObstacleScale(shapes, i); // проверяем столкновение фигур
			ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window); // рисуем фигуру
			if (coordinateActive && std::find(focus.begin(), focus.end(), i) != focus.end()) ShapeDealer::DrawPosition(shapes[i], window);
		}
	}
	
	static void Tip(RenderWindow& window) {
		
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
				text.setPosition(-960.f, - 540.f + i);
				window.draw(text);
			}
		}
		file.close();
	}
};
