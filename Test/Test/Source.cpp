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

	RenderWindow window{ VideoMode(1920, 1080), L"�������������� ������" };

	std::vector<Figure*> shapes; // ��� �������� ������
	Clock clock; // ��� ������ �����
	std::string cmd; // ��� ��������� ������
	unsigned int focus = 0;
	figureID id = CIRCLE; // id ������� ������
	bool cmdActive = false;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
			clock.restart();
			time /= CMD::SPEED; // ��������� �����

			if (event.type == Event::Closed) window.close();

			if (!cmdActive) CMD::Key(shapes, event, focus, id);
			else CMD::Text(shapes, cmd, event, focus, id);

			if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))
				if (time >= CMD::TIME) {
					cmdActive = !cmdActive;
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