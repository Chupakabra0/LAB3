#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "ShapeDealer.h"
#include <iostream>
#include "Circle.h"

using namespace sf;

struct Const {
	Const() = delete;
	~Const() = delete;
	constexpr static float SPEED = 1000.f;
	constexpr static float TIME = 200.f;
	constexpr static float MOVE = 1.f;
	constexpr static float ANGLE = 0.1f;
	constexpr static float SCALE_PLUS = 1.f;
	constexpr static float SCALE_MINUS = -1.f;
};

//float Const::TIME = 200.f;

int main(void) {

	RenderWindow window{ VideoMode(600, 600), L"Геометрические фигуры" };

	std::vector<IShape*> shapes;

	Clock clock;

	while (window.isOpen()) {

		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		time /= Const::SPEED;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			if (!shapes.empty()) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Up)) { //вверх
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, -Const::MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Down)) { //вниз
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, Const::MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Left)) { //влево
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(-Const::MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Right)) { //вправо
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(Const::MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::E) && time >= Const::TIME) { //поворот влево
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(-Const::ANGLE));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Q) && time >= Const::TIME) { //поворот вправо
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(Const::ANGLE));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::W) && time >= Const::TIME) { //увеличение масштаба
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(Const::SCALE_PLUS));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::S) && time >= Const::TIME) { //уменьшение масштаба
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(Const::SCALE_MINUS));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Z) && time >= Const::TIME) { //уменьшение масштаба
					ShapeDealer::LegacyCondition(dynamic_cast<IShape*>(shapes[shapes.size() - 1]));
					time = 0.f;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::X) && time >= Const::TIME) { //уменьшение масштаба
					ShapeDealer::FirstCondition(dynamic_cast<IShape*>(shapes[shapes.size() - 1]));
					time = 0.f;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Add) && time >= Const::TIME) {
				Circle* temp = new Circle(XY(200.f), Color(10, 20, 30, 40));
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
