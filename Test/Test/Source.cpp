#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Point.h"
#include "ShapeDealer.h"
#include <iostream>
//#define WINDOW

using namespace sf;

int main(void) {

	RenderWindow window{ VideoMode(600, 600), L"Геометрические фигуры" };

	std::vector<IShape*> shapes;

	Clock clock;

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asMicroseconds();
		time /= 1000.f;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (!shapes.empty()) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, -1.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, 1.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(-1.f, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(1.f, 0.f));
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Add) && time >= 200.f) {
				Point* temp = new Point(XY(200.f), RGB(10, 20, 30));
				shapes.push_back(dynamic_cast<IDraw*>(temp));
				time = 0.f;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::E) && time >= 200.f) {
				ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), -0.1f);
				time = 0.f;
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Q) && time >= 200.f) {
				ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), 0.1f);
				time = 0.f;
			}
		}
		window.clear();
		for (auto i = 0; i < shapes.size(); i++) {
			std::cout << i + 1 << std::endl;
			ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}
