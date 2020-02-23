#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "ShapeDealer.h"
#include <iostream>
#include "Circle.h"

#include <string>
#include <sstream>
#include <algorithm>

using namespace sf;

enum figureID {
	CIRCLE
};

std::string to_string(ENUM id) {
	switch (id) {
	case ENUMERATOR: return typeid(Circle).name() + std::string("class ").size();
	default: return "unknown";
	}
}

struct Const {
	Const() = delete;
	~Const() = delete;

	constexpr static float SPEED = 1000.f;
	constexpr static float TIME = 500.f;
	constexpr static float MOVE = 1.f;
	constexpr static float ANGLE = 0.1f;
	constexpr static float SCALE_PLUS = 1.f;
	constexpr static float SCALE_MINUS = -1.f;

	const static std::string SET;
	const static std::string CREATE;
	const static std::string POSITION;

	static void Key(std::vector<IShape*>& shapes, Event& event, float& time, unsigned int& focus, figureID& id) {
		if (time >= Const::TIME) {
			if (!shapes.empty() && event.type == Event::KeyPressed) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[focus]), XY(-MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[focus]), XY(MOVE, 0.f));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[focus]), XY(0.f, -MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
					ShapeDealer::Move(dynamic_cast<IMove*>(shapes[focus]), XY(0.f, MOVE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[focus]), Angle(-ANGLE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
					ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[focus]), Angle(ANGLE));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[focus]), Scale(SCALE_PLUS));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
					ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[focus]), Scale(SCALE_MINUS));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
					ShapeDealer::LegacyCondition(dynamic_cast<IShape*>(shapes[focus]));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
					ShapeDealer::FirstCondition(dynamic_cast<IShape*>(shapes[focus]));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::PageDown)) {
					ShapeDealer::SwitchFocus(dynamic_cast<Figure*>((shapes[focus])));
					if (focus != 0) focus--;
					else focus = shapes.size() - 1;
					ShapeDealer::SwitchFocus(dynamic_cast<Figure*>((shapes[focus])));
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::PageUp)) {
					ShapeDealer::SwitchFocus(dynamic_cast<Figure*>((shapes[focus])));
					if (focus != shapes.size() - 1) focus++;
					else focus = 0;
					ShapeDealer::SwitchFocus(dynamic_cast<Figure*>((shapes[focus])));
				}
			}
			else if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Key::Add) {
					std::vector<float> coordinates;
					CreateFigure(shapes, coordinates, focus, id);
				}
			}
			time = 0.f;
		}
	}

	static void Text(std::vector<IShape*>& shapes, std::string& string, const Event& event, unsigned int& focus, figureID& id) {
		if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == '\b') {
				if (!string.empty()) string.erase(string.cend() - 1);
			}
			else if (event.text.unicode == 13) Check(shapes, string, focus, id);
			else if (event.text.unicode != 43) string += {static_cast<char>(event.text.unicode)};
		}
	}

private:
	static void Check(std::vector<IShape*>& shapes, std::string& string, unsigned int& focus, figureID& id) {
		if (string.find("Create", 0) != -1) {
			if (string.find(to_string(CIRCLE), 0) != -1) {
				auto coordinates = Convert(string);
				CreateFigure(shapes, coordinates, focus, id);
			}
		}
		else if (string.find("Set", 0) != -1) {
			if (string.find("Position", 0) != -1) {
				auto coordinates = Convert(string);
				SetFigurePosition(dynamic_cast<IMove*>(shapes[focus]), coordinates);
			}
		}
		string.erase();
	}

	static std::vector<float> Convert(std::string& string) {
		string = NumberCheck(string);
		std::replace(string.begin(), string.end(), '_', ' ');
		std::istringstream ss(string);
		return std::vector<float>{ std::istream_iterator<float>(ss), {} };
	}

	static std::string NumberCheck(std::string& string) {
		std::string result;
		const auto size = string.size();
		for (auto i = 0; i < size; i++) {
			if (string[i] == '_' || (string[i] >= '0' && string [i] <= '9')){
				result += string[i];
			}
		}
		return result;
	}

	static void CreateFigure(std::vector<IShape*>& shapes, std::vector<float>& coordinates, unsigned int& focus, figureID& id) {
		if (!shapes.empty()) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>((shapes[focus])));
		Figure* temp = nullptr;
		switch (id) {
			case CIRCLE: {
				XY xy;
				Color color;
				float radius = 10.f;
				if (coordinates.empty()) {
					xy.setXY(0.f, 0.f);
					color = Color::Red;
				}
				else if (coordinates.size() == 1) {
					xy.setXY(coordinates[0], coordinates[0]);
					color = Color::Red;
				}
				else if (coordinates.size() == 2) {
					xy.setXY(coordinates[0], coordinates[1]);
					color = Color::Red;
				}
				else if (coordinates.size() == 3 || coordinates.size() == 4 || coordinates.size() == 5) {
					xy.setXY(coordinates[0], coordinates[1]);
					radius = coordinates[2];
					color = Color::Red;
				}
				else if (coordinates.size() >= 6) {
					xy.setXY(coordinates[0], coordinates[1]);
					radius = coordinates[2];
					color = Color(coordinates[3], coordinates[4], coordinates[5]);
				}
				temp = new Circle(XY(xy.getX(), xy.getY()), color, radius);
				break;
			}
			default: {
				break;
			}
		}
		shapes.push_back(dynamic_cast<IDraw*>(temp));
		focus = shapes.size() - 1;
		ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus]));
	}

	static void SetFigurePosition(IMove* shape, std::vector<float>& coordinates) {
		if (coordinates.size() > 1) ShapeDealer::SetPosition(shape, XY(coordinates[0], coordinates[1]));
		else if (coordinates.size() == 1) ShapeDealer::SetPosition(shape, XY(coordinates[0]));
		else ShapeDealer::SetPosition(shape, XY(0));
	}
};

const std::string Const::SET = "Set"; 
const std::string Const::CREATE = "Create";
const std::string Const::POSITION = "Position";

int main(void) {

	RenderWindow window{ VideoMode(1000, 1000), L"Геометрические фигуры" };

	std::vector<IShape*> shapes; // тут хранятся фигуры
	Clock clock; // тут тикает время
	std::string cmd; // тут командная строка
	unsigned int focus = 0; // тут номер фигуры под фокусом TODO сделать массив фокусируемых фигур
	figureID id = CIRCLE; // id текущей фигуры

	while (window.isOpen()) {

		auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds()); 
		time /= Const::SPEED; // обновляем время

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			Const::Key(shapes, event, time, focus, id);
			Const::Text(shapes, cmd, event, focus, id);
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