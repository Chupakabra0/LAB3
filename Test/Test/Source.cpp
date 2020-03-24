#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "CMD.h"
#include "ShapeDealer.h"

using namespace sf;

struct Main {
	static void FileProcedure(std::vector<Figure*>& shapes, std::vector<int>& focus) {

		string temp;																						// ������ � ������� �������� �����
		do {
			cout << "Do you want to open config-file?" << endl;												// ������� ������
			getline(cin, temp);																				// ������ �����
			system("cls");
		} while (!(temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+"
			||
			temp == "no" || temp == "n" || temp == "No" || temp == "N" || temp == "-"));					// � ��� ���� �� ������� ������ �����

		if (temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+") {					// ���� ����� �������������, �� �������� ����� � �����
			ifstream config("tex.txt");
			if (!config.is_open()) {
				cout << "ERROR" << endl;
				system("cls");
			}
			while (!config.eof()) {
				string command;
				getline(config, command);
				CMD::Check(shapes, command, focus);
			}
		}
	}

	static void TextDisplay(RenderWindow& window, View camera, string cmd, bool cmdActive) {
		Text cmdText;
		Font font;
		font.loadFromFile("BAUHS93.ttf");
		cmdText.setString(cmd);
		cmdText.setFont(font);

		Text cmdActiveText;
		cmdActiveText.setFont(font);
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

	static void Program() {
		std::vector<Figure*> shapes;																		// ��� �������� ������
		Clock clock;																						// ��� ������ �����
		std::string cmd;																					// ��� ��������� ������
		std::vector<int> focus = { 0 };																		// ������ �����, ������� � ������
		auto id = CIRCLE;																					// id ������� ������
		auto cmdActive = false;																				// ������� �� �������

		FileProcedure(shapes, focus);																		// �������� ���������

		ContextSettings settings;																			// ��������� �����������
		settings.antialiasingLevel = 10;																	// ���������

		RenderWindow window{ VideoMode(1920, 1080), L"�������������� ������" };		// �������� ����
		View camera;																						// �������� ������
		camera.reset(FloatRect(0.f, 0.f, 1920.f, 1080.f));			// ����� ������

		while (window.isOpen()) {																			// ���� ���� �������

			Event event;
			while (window.pollEvent(event)) {																// ����� �������

				auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / CMD::SPEED;		// ��������� �����
				clock.restart();																			// ������������� ����

				if (event.type == Event::Closed) window.close();											// ���� ����� �������, ��������� ����

				if (!cmdActive) CMD::Key(shapes, event, focus, id);											// ���� ������� ���������, ����� ���� � ����������
				else CMD::Text(shapes, cmd, event, focus);													// ����� ����� ���� � ���������� � ��������� �������

				if (Keyboard::isKeyPressed(Keyboard::Key::Tilde))											// ������������ ������� �� "������"
					if (time >= CMD::TIME) {
						cmdActive = !cmdActive;
						cmd.erase();
						time = 0.f;
					}
			}

			window.clear();																					// ������ ���� ����� ���������� ������ �����
			for (auto i = 0; i < shapes.size(); i++) {
				ShapeDealer::ObstacleScale(shapes, i);														// ��������� ������������ �����
				ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window);									// ������ ������
			}

			if (!shapes.empty() && !focus.empty()) camera.setCenter(shapes[focus[0]]->GetPosition().getX(), shapes[focus[0]]->GetPosition().getY());
																											// ������ ������, � ������� ����������� ������
			TextDisplay(window, camera, cmd, cmdActive);													// ������� �����

			window.setView(camera);																			// ������������� ������
			window.display();																				// ��������� ����
		}
	}
};

auto main() -> int {

	Main::Program(); // ��������� �������, ������� �������� �� ���� ���������
	return EXIT_SUCCESS;
}
