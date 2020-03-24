#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "CMD.h"
#include "ShapeDealer.h"

using namespace sf;

struct Main {
	static void FileProcedure(std::vector<Figure*>& shapes, std::vector<int>& focus) {

		std::string temp;									// строка в которой хранится ответ
		auto file = false;									// грузить ли файл конфигурации

		do {
			std::cout << "Do you want to open config-file?" << std::endl;
			getline(cin, temp);
			system("cls");
		} while (!(temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+"
			||
			temp == "no" || temp == "n" || temp == "No" || temp == "N" || temp == "-"));

		if (temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+") {
			file = true;
		}

		if (file) {
			ifstream config("tex.txt");
			while (!config.eof()) {
				std::string command;
				getline(config, command);
				CMD::Check(shapes, command, focus);
			}
		}
	}

	static void Program() {
		std::vector<Figure*> shapes;						// тут хранятся фигуры
		Clock clock;										// тут тикает время
		View camera;										// камера
		std::string cmd;									// тут командная строка
		std::vector<int> focus = { 0 };						// вектор фигур, которые в фокусе
		auto id = CIRCLE;									// id текущей фигуры
		auto cmdActive = false;								// активна ли консоль

		FileProcedure(shapes, focus);

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

			Text cmdText;
			Font font;
			font.loadFromFile("BAUHS93.ttf");
			cmdText.setString(cmd);
			cmdText.setFont(font);

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

			if (!shapes.empty() && !focus.empty()) {
				camera.setCenter(shapes[focus[0]]->GetPosition().getX(), shapes[focus[0]]->GetPosition().getY());
			}
			cmdActiveText.setPosition(camera.getCenter().x + 750.f, camera.getCenter().y - 540.f);
			cmdText.setPosition(camera.getCenter().x - 960.f, camera.getCenter().y - 540.f);

			window.draw(cmdText);
			window.draw(cmdActiveText);

			window.setView(camera);
			window.display();
		}
	}
};

int main() {

	Main::Program();
	return EXIT_SUCCESS;
}
