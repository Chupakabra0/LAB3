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

	RenderWindow window(VideoMode(200, 200), "SFML Works!");

	// ������� ���� ����������. �����������, ���� ������� ����
	while (window.isOpen())
	{
		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				// ����� ��������� ���
				window.close();
		}
		// ��������� ����	
		window.display();
	}

	Point first(100.f, 100.f);

	std::cout << "First: ";
	output(&first);

	std::cout << "+(1.f; 2.f)";
	first.SetDot(Dot(first.GetDot().GetPosition().getX() + 1.f, first.GetDot().GetPosition().getY() + 2.f));
	output(&first);

	std::cout << "=(0.f; 0.f)";
	first.SetDot(Dot(0.f, 0.f));
	output(&first);

	std::cout << "Previous:" << std::endl;
	first.Previous();
	first.Previous();

	output(&first);

	system("pause > NUL");
	return EXIT_SUCCESS;
}
