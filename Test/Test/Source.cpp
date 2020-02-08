#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Point.h"
#include <windows.h>
#include <iostream>
//#define WINDOW

using namespace sf;

int main(void) {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Point first(100.f, 100.f);

	RenderWindow window(VideoMode(600, 600), L"Геометрические фигуры");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
				first.ChangePosition(XY(0, -1.f));
			}
		}
		window.clear();
		first.Draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}
