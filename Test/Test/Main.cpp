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
	//

	//
	else {
		config.open("tex.txt", ios_base::out | ios_base::trunc);
	}
	config.close();
}

void Main::TextDisplay(RenderWindow& window, View camera, string cmd, bool cmdActive, figureID id) {

	Text cmdText;
	Text cmdActiveText;
	Text idText;
	TextProcedure(cmdText, std::move(cmd));
	TextProcedure(cmdActiveText, "");
	TextProcedure(idText, to_string(id));

	Font font;
	font.loadFromFile("BAUHS93.ttf");
	cmdActiveText.setFont(font);
	cmdText.setFont(font);
	idText.setFont(font);

	if (cmdActive) {
		cmdActiveText.setString("CMD mode");
		cmdActiveText.setFillColor(Color::Green);
	}
	else {
		cmdActiveText.setString("Manual mode");
		cmdActiveText.setFillColor(Color::Red);
	}

	idText.setFillColor(Color(3, 238, 255));

	cmdActiveText.setPosition(camera.getCenter().x + 750.f, camera.getCenter().y - 540.f);
	idText.setPosition(camera.getCenter().x + 810.f, camera.getCenter().y + 410.f);
	cmdText.setPosition(camera.getCenter().x - 960.f, camera.getCenter().y - 540.f);

	window.draw(cmdText);
	window.draw(cmdActiveText);
	window.draw(idText);
}

void Main::TextProcedure(Text& text, sf::String string) {
	text.setString(string);
}

void Main::Program() {
	std::vector<Figure*> shapes; // тут хранятся фигуры
	Clock clock; // тут тикает время
	std::string cmd; // тут командная строка
	std::vector<int> focus = {0}; // вектор фигур, которые в фокусе
	vector<figureID> typeFigure = {
		CIRCLE,
		TRIANGLE,
		DIAMOND,
		STAR,
		TRAPEZOID
	};
	
	auto idFigure = 0; // id текущей фигуры
	auto cmdActive = false; // активна ли консоль
	auto coordinateActive = true; // активно ли отображение координат
	auto tip = false; //активна ли справка на экране

	FileProcedure(shapes, focus); // файловая процедура

	ContextSettings settings; // настройки детализации
	settings.antialiasingLevel = 10; // рисования

	RenderWindow window{VideoMode(1920, 1080), L"Геометрические фигуры"}; // создание окна
	View camera; // создание камеры
	View temp;
	camera.reset(FloatRect(0.f, 0.f, 1920.f, 1080.f)); // ресет камеры
	camera.setCenter(0.f, 0.f);

	while (window.isOpen()) {
		// пока окно открыто

		Event event;
		while (window.pollEvent(event)) {
			// ловим событие

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / CMD::SPEED; // обновляем время
			clock.restart(); // перезапускаем часы

			if (event.type == sf::Event::Closed) window.close(); // если нажат крестик, закрываем окно

			if (!tip) {
				if (!cmdActive) CMD::Key(shapes, event, focus, typeFigure[idFigure]); // если консоль неактивна, ловим ввод с клавиатуры
				else CMD::Text(shapes, cmd, event, focus); // иначе ловим ввод с клавиатуры и обновляем консоль

			}

			if (time >= CMD::TIME) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Tilde)) { // переключение режимов на "тильду"
					cmdActive = !cmdActive;
					cmd.erase();
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::I)) {
					if (idFigure + 1 >= typeFigure.size()) {
						idFigure = 0;
					}
					else idFigure++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::K)) {
					if (idFigure - 1 < 0) {
						idFigure = typeFigure.size() - 1;
					}
					else idFigure--;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Comma)) {
					coordinateActive = !coordinateActive;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::F1)) {
					tip = !tip;
					camera.setCenter(0.f, 0.f);
				}
				if (tip) {
					if (Keyboard::isKeyPressed(Keyboard::Key::Up) && camera.getCenter().y > 0.f) {
						camera.setCenter(camera.getCenter().x, camera.getCenter().y - 10.f);
					}
					if (Keyboard::isKeyPressed(Keyboard::Key::Down) && camera.getCenter().y < 800.f) {
						camera.setCenter(camera.getCenter().x, camera.getCenter().y + 10.f);
					}
				}
				time = 0.f;
			}
		}

		window.clear(); // чистим окно перед рисованием нового кадра

		if (tip) {
			Tip(window); // выводим справку
		}
		else {
			DrawProccess(window, shapes, focus, coordinateActive); // выводим фигуры
			TextDisplay(window, camera, cmd, cmdActive, typeFigure[idFigure]); // выводим текст
			if (!shapes.empty() && !focus.empty()) {
				camera.setCenter(shapes[focus[0]]->GetPosition().GetX(), shapes[focus[0]]->GetPosition().GetY());
			}
		}
		
		window.setView(camera); // устанавливаем камеру
		window.display(); // обновляем кадр
	}
}
