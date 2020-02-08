#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Point.h"
#include "ShapeDealer.h"
//#define WINDOW

using namespace sf;

int main(void) {

	Point a(100.f, 100.f);

	RenderWindow window{ VideoMode(600, 600), L"Геометрические фигуры" };

	ShapeDealer::Move(&a, XY(1));

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
				a.ChangePosition(XY(0.f, -1.f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
				a.ChangePosition(XY(0.f, 1.f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				a.ChangePosition(XY(-1.f, 0.f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				a.ChangePosition(XY(1.f, 0.f));
			}
		}
		window.clear();
		ShapeDealer::Draw(&a, window);
		window.display();
	}

	return EXIT_SUCCESS;
}
