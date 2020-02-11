#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Point.h"
#include "ShapeDealer.h"
#include <iostream>

using namespace sf;

struct Const {
	constexpr static float SPEED = 1000.f;
	constexpr static float TIME = 200.f;
	constexpr static float MOVE = 1.f;
	constexpr static float ANGLE = 0.1f;
	constexpr static float SCALE_PLUS = 1.f;
	constexpr static float SCALE_MINUS = -1.f;
};

//float Const::TIME = 200.f;

int main(void) {

	RenderWindow window{ VideoMode(600, 600), L"�������������� ������" };

	std::vector<IShape*> shapes;

	Clock clock;

	while (window.isOpen()) {

		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		time /= Const::SPEED;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (!shapes.empty()) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Up)) { //�����
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, -Const::MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Down)) { //����
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, Const::MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Left)) { //�����
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(-Const::MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Right)) { //������
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(Const::MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::E) && time >= Const::TIME) { //������� �����
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(-Const::ANGLE));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Q) && time >= Const::TIME) { //������� ������
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(Const::ANGLE));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::W) && time >= Const::TIME) { //���������� ��������
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(Const::SCALE_PLUS));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::S) && time >= Const::TIME) { //���������� ��������
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(Const::SCALE_MINUS));
					time = 0.f;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Add) && time >= Const::TIME) {
				Point* temp = new Point(XY(200.f), RGB(10, 20, 30));
				shapes.push_back(dynamic_cast<IDraw*>(temp));
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
