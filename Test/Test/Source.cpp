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
	constexpr static float TIME = 500.f;
	constexpr static float MOVE = 1.f;
	constexpr static float ANGLE = 0.1f;
	constexpr static float SCALE_PLUS = 1.f;
	constexpr static float SCALE_MINUS = -1.f;
	static void Key(std::vector<IShape*>& shapes, const Event& event, float& time) {
		if (time >= Const::TIME) {
			if (!shapes.empty() && event.type == Event::KeyPressed) {
				switch (event.key.code) {
				case Keyboard::Key::Up: {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, -Const::MOVE));
					break;
				}
				case Keyboard::Key::Down: {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(0.f, Const::MOVE));
					break;
				}
				case Keyboard::Key::Left: {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(-Const::MOVE, 0.f));
					break;
				}
				case Keyboard::Key::Right: {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[shapes.size() - 1]), XY(Const::MOVE, 0.f));
					break;
				}
				case Keyboard::Key::E: {
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(-Const::ANGLE));
					break;
				}
				case Keyboard::Key::Q: {
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[shapes.size() - 1]), Angle(Const::ANGLE));
					break;
				}
				case Keyboard::Key::W: {
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(Const::SCALE_PLUS));
					break;
				}
				case Keyboard::Key::S: {
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[shapes.size() - 1]), Scale(Const::SCALE_MINUS));
					break;;
				}
				case Keyboard::Key::Z: {
					ShapeDealer::LegacyCondition(dynamic_cast<IShape*>(shapes[shapes.size() - 1]));
					break;
				}
				case Keyboard::Key::X: {
					ShapeDealer::FirstCondition(dynamic_cast<IShape*>(shapes[shapes.size() - 1]));
					break;
				}
				default: break;
				}
			}
			else if (event.type == Event::KeyReleased) {
				switch (event.key.code) {
				case Keyboard::Key::Add: {
					Circle* temp = new Circle(XY(200.f), Color(100, 255, 30, 255), 2.f);
					shapes.push_back(dynamic_cast<IDraw*>(temp));
					break;
				}
				default: break;
				}
			}
			time = 0.f;
		}
	}

};


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
			Const::Key(shapes, event, time);
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
