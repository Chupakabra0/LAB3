#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "CMD.h"
#include "ShapeDealer.h"

using namespace sf;

int main() {

	std::string temp;
	auto file = false;

	std::cout << "Do you want to open config-file?" << std::endl;
	getline(cin, temp);

	if (temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y") {
		file = true;
	}

	std::vector<Figure*> shapes; // тут хранятся фигуры
	Clock clock; // тут тикает время
	View camera;
	std::string cmd; // тут командная строка
	std::vector<int> focus = { 0 };
	auto id = CIRCLE; // id текущей фигуры
	auto cmdActive = false;

	if(file) {
		ifstream config("tex.txt");
		while (!config.eof()) {
			std::string command;
			getline(config, command);
			CMD::Check(shapes, command, focus);
		}
	}

	ContextSettings settings;
	settings.antialiasingLevel = 10;
	RenderWindow window{ VideoMode(1920, 1080), L"Геометрические фигуры" };
	camera.reset(sf::FloatRect(0, 0, 1920, 1080));

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
			clock.restart();
			time /= CMD::SPEED; // обновляем время

			if (event.type == Event::Closed) window.close();

			if (!cmdActive) CMD::Key(shapes, event, focus, id);
			else CMD::Text(shapes, cmd, event, focus);

			if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))
				if (time >= CMD::TIME) {
					cmdActive = !cmdActive;
					cmd.erase();
					time = 0.f;
				}
		}

		window.clear();
		for (auto i = 0; i < shapes.size(); i++) {
			ShapeDealer::ObstacleScale(shapes, i);
			ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window);
		}

		//
		if (!shapes.empty() && !focus.empty()) {
			camera.setCenter(shapes[focus[0]]->GetPosition().getX(), shapes[focus[0]]->GetPosition().getY());
		}
		window.setView(camera);

		Text cmdText;
		Font font;
		font.loadFromFile("BAUHS93.ttf");
		cmdText.setString(cmd);
		cmdText.setFont(font);
		window.draw(cmdText);

		Text cmdActiveText;
		cmdActiveText.setFont(font);
		if (cmdActive) {
			cmdActiveText.setString("CMD mode");
			cmdActiveText.setFillColor(Color::Green);
		}
		else {
			cmdActiveText.setString("Manual mode");
			cmdActiveText.setFillColor(Color::Red);
		}
		cmdActiveText.setPosition(1700.f, 0.f);
		window.draw(cmdActiveText);
		//

		window.display();
	}

	return EXIT_SUCCESS;
}
