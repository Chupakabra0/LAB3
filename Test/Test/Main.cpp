#include "Main.h"

#include <iostream>
#include <string>
#include <fstream>
#include <utility>

#include "CMD.h"

using namespace sf;
using namespace std;

void Main::FileProcedure(std::vector<Figure*>& shapes, std::vector<int>& focus) {

	string temp; // строка в которой хранится ответ
	do {
		cout << "Do you want to open config-file?" << endl; // выводим вопрос
		getline(cin, temp); // вводим ответ
		system("cls");
	}
	while (!(temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+"
		||
		temp == "no" || temp == "n" || temp == "No" || temp == "N" || temp == "-"));
	// и так пока не получим нужный ответ


	ifstream config;
	if (temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+") {
		// если ответ положительный, то проводим читку с файла
		config.open("tex.txt", ios_base::in);
		if (!config.is_open()) {
			cout << "ERROR" << endl;
			system("cls");
		}
		else {
			while (!config.eof()) {
				string command;
				getline(config, command);
				CMD::Check(shapes, command, focus);
			}
		}
	}
	else {
		config.open("tex.txt", ios_base::out | ios_base::trunc);
	}
	config.close();
}

void Main::TextDisplay(RenderWindow& window, View camera, string cmd, bool cmdActive) {

	Text cmdText;
	Text cmdActiveText;
	TextProcedure(cmdText, std::move(cmd));
	TextProcedure(cmdActiveText, "");

	Font font;
	font.loadFromFile("BAUHS93.ttf");
	cmdActiveText.setFont(font);
	cmdText.setFont(font);

	if (cmdActive) {
		cmdActiveText.setString("CMD mode");
		cmdActiveText.setFillColor(Color::Green);
	}
	else {
		cmdActiveText.setString("Manual mode");
		cmdActiveText.setFillColor(Color::Red);
	}


	cmdActiveText.setPosition(camera.getCenter().x + 750.f, camera.getCenter().y - 540.f);
	cmdText.setPosition(camera.getCenter().x - 960.f, camera.getCenter().y - 540.f);

	window.draw(cmdText);
	window.draw(cmdActiveText);
}

void Main::TextProcedure(Text& text, std::string string) {
	text.setString(string);
}

void Main::Program() {
	std::vector<Figure*> shapes; // тут хранятся фигуры
	Clock clock; // тут тикает время
	std::string cmd; // тут командная строка
	std::vector<int> focus = {0}; // вектор фигур, которые в фокусе
	auto id = CIRCLE; // id текущей фигуры
	auto cmdActive = false; // активна ли консоль

	FileProcedure(shapes, focus); // файловая процедура

	ContextSettings settings; // настройки детализации
	settings.antialiasingLevel = 10; // рисования

	RenderWindow window{VideoMode(1920, 1080), L"Геометрические фигуры"}; // создание окна
	View camera; // создание камеры
	camera.reset(FloatRect(0.f, 0.f, 1920.f, 1080.f)); // ресет камеры

	while (window.isOpen()) {
		// пока окно открыто

		Event event;
		while (window.pollEvent(event)) {
			// ловим событие

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / CMD::SPEED; // обновляем время
			clock.restart(); // перезапускаем часы

			if (event.type == sf::Event::Closed) window.close(); // если нажат крестик, закрываем окно

			if (!cmdActive) CMD::Key(shapes, event, focus, id); // если консоль неактивна, ловим ввод с клавиатуры
			else CMD::Text(shapes, cmd, event, focus); // иначе ловим ввод с клавиатуры и обновляем консоль

			if (Keyboard::isKeyPressed(Keyboard::Key::Tilde)) // переключение режимов на "тильду"
				if (time >= CMD::TIME) {
					cmdActive = !cmdActive;
					cmd.erase();
					time = 0.f;
				}
		}

		window.clear(); // чистим окно перед рисованием нового кадра
		for (auto i = 0; i < shapes.size(); i++) {
			ShapeDealer::ObstacleScale(shapes, i); // проверяем столкновение фигур
			ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window); // рисуем фигуру
			if (std::find(focus.begin(), focus.end(), i) != focus.end()) ShapeDealer::DrawPosition(shapes[i], window);
		}

		if (!shapes.empty() && !focus.empty()) camera.setCenter(shapes[focus[0]]->GetPosition().GetX(),
																shapes[focus[0]]->GetPosition().GetY());
		// меняем фигуру, к которой приклеплена камера
		TextDisplay(window, camera, cmd, cmdActive); // выводим текст

		window.setView(camera); // устанавливаем камеру
		window.display(); // обновляем кадр
	}
}
