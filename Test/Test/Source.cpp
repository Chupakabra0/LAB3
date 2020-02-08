#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Point.h"
//#define WINDOW

using namespace sf;

int main(void) {

	Point first(100.f, 100.f);

	RenderWindow window(VideoMode(600, 600), L"Геометрические фигуры");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
				first.ChangePosition(XY(0.f, -1.f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
				first.ChangePosition(XY(0.f, 1.f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
				first.ChangePosition(XY(-1.f, 0.f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
				first.ChangePosition(XY(1.f, 0.f));
			}
		}
		window.clear();
		first.Draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}
