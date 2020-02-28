#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "ShapeDealer.h"
#include <iostream>
#include "Circle.h"

#include <string>
#include <algorithm>
#include "CMD.h"

using namespace sf;

int main(void) {

	ContextSettings settings;
	settings.antialiasingLevel = 10;

	RenderWindow window{ VideoMode(1000, 1000), L"Геометрические фигуры" };

	std::vector<IShape*> shapes; // тут хранятся фигуры
	Clock clock; // тут тикает время
	std::string cmd; // тут командная строка
	unsigned int focus = 0; // тут номер фигуры под фокусом TODO сделать массив фокусируемых фигур
	figureID id = CIRCLE; // id текущей фигуры
	bool CMDActive = false;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
			clock.restart();
			time /= CMD::SPEED; // обновляем время

			if (event.type == Event::Closed) window.close();

			if (!CMDActive) CMD::Key(shapes, event, focus, id);
			else CMD::Text(shapes, cmd, event, focus, id);

			if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))
				if (time >= CMD::TIME) {
					CMDActive = !CMDActive;
					cmd.erase();
					time = 0.f;
				}
		}

		window.clear();
		for (auto i = 0; i < shapes.size(); i++) {
			std::cout << i + 1 << std::endl;
			ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window);
		}

		//
		Text text;
		Font font;
		font.loadFromFile("BAUHS93.ttf");
		text.setString(cmd);
		text.setFont(font);
		window.draw(text);
		//


		window.display();
	}

	return EXIT_SUCCESS;
}