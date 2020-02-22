#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "ShapeDealer.h"
#include <iostream>
#include "Circle.h"

#include <string>
#include <sstream>

using namespace sf;

struct Const {
	Const() = delete;
	~Const() = delete;
	constexpr static float SPEED = 1000.f;
	constexpr static float TIME = 500.f;
	constexpr static float MOVE = 1.f;
	constexpr static float ANGLE = 0.1f;
	constexpr static float SCALE_PLUS = 1.f;
	constexpr static float SCALE_MINUS = -1.f;

	static void Key(std::vector<IShape*>& shapes, Event& event, float& time) {
		if (time >= Const::TIME) {
			if (!shapes.empty() && event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(-MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, -MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(-ANGLE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(ANGLE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(SCALE_PLUS));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(SCALE_MINUS));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
					ShapeDealer::LegacyCondition(dynamic_cast<IShape*>(shapes[shapes.size() - 1]));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
					ShapeDealer::FirstCondition(dynamic_cast<IShape*>(shapes[shapes.size() - 1]));
				}
			}
			else if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Key::Add) {
					Circle* temp = new Circle(XY(200.f), Color(100, 255, 30, 255), 2.f);
					shapes.push_back(dynamic_cast<IDraw*>(temp));
				}
			}
			time = 0.f;
		}
	}

	static void Text(std::string& string, const Event& event) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b') {
				if (!string.empty()) string.erase(string.cend() - 1);
			}
			else if (event.text.unicode == 13) Check(string);
			else string += {static_cast<char>(event.text.unicode)};
		}
	}

	static void Check(const std::string& string) {
		if (!string.find("Set")) {

		}
	}
};

int main(void) {

	RenderWindow window{ VideoMode(600, 600), L"�������������� ������" };

	std::vector<IShape*> shapes;
	Clock clock;

	std::string cmd;

	while (window.isOpen()) {

		auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		time /= Const::SPEED;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			Const::Key(shapes, event, time);
			Const::Text(cmd, event);
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