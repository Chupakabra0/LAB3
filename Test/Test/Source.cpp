#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Point.h"
#include <windows.h>
#include <iostream>
//#define WINDOW

using namespace sf;

void output(Point* point) {
	std::cout << "X: " << point->GetDot().GetPosition().getX() << " Y: " << point->GetDot().GetPosition().getY() << std::endl;
}

int main(void) {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Point first(100.f, 100.f);

	RenderWindow window(VideoMode(600, 600), L"Геометрические фигуры");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyPressed  || event.type == Event::Closed) window.close();
		}
		first.Draw(window);
		window.display();
	}

	output(&first);

	system("pause > NUL");
	return EXIT_SUCCESS;
}
