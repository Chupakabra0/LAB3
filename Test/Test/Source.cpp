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

	std::vector<Figure*> shapes; // ��� �������� ������
	Clock clock; // ��� ������ �����
	std::string cmd; // ��� ��������� ������
	std::vector<int> focus = { 0 };
	auto id = CIRCLE; // id ������� ������
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
	RenderWindow window{ VideoMode(1920, 1080), L"�������������� ������" };

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
			clock.restart();
			time /= CMD::SPEED; // ��������� �����

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
		for (auto i : focus) std::cout << i;
		cout << endl;

		//
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
