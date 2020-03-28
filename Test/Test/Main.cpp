#include "Main.h"

#include <iostream>
#include <string>
#include <fstream>
#include <utility>

#include "CMD.h"

using namespace sf;
using namespace std;

void Main::FileProcedure(std::vector<Figure*>& shapes, std::vector<int>& focus) {

	string temp; // ������ � ������� �������� �����
	do {
		cout << "Do you want to open config-file?" << endl; // ������� ������
		//getline(cin, temp); // ������ �����
		temp = "+";
		system("cls");
	}
	while (!(temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+"
		||
		temp == "no" || temp == "n" || temp == "No" || temp == "N" || temp == "-"));
	// � ��� ���� �� ������� ������ �����


	ifstream config;
	if (temp == "yes" || temp == "y" || temp == "Yes" || temp == "Y" || temp == "+") {
		// ���� ����� �������������, �� �������� ����� � �����
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
	std::vector<Figure*> shapes; // ��� �������� ������
	Clock clock; // ��� ������ �����
	std::string cmd; // ��� ��������� ������
	std::vector<int> focus = {0}; // ������ �����, ������� � ������
	vector<figureID> typeFigure = {
		CIRCLE,
		TRIANGLE,
		DIAMOND,
		STAR,
		TRAPEZOID
	};
	
	auto idFigure = 0; // id ������� ������
	auto cmdActive = false; // ������� �� �������
	auto coordinateActive = true; // ������� �� ����������� ���������
	auto tip = false; //������� �� ������� �� ������

	FileProcedure(shapes, focus); // �������� ���������

	ContextSettings settings; // ��������� �����������
	settings.antialiasingLevel = 10; // ���������

	RenderWindow window{VideoMode(1920, 1080), L"�������������� ������"}; // �������� ����
	View camera; // �������� ������
	camera.reset(FloatRect(0.f, 0.f, 1920.f, 1080.f)); // ����� ������
	camera.setCenter(0.f, 0.f);

	while (window.isOpen()) {
		// ���� ���� �������

		Event event;
		while (window.pollEvent(event)) {
			// ����� �������

			auto time = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / CMD::SPEED; // ��������� �����
			clock.restart(); // ������������� ����

			if (event.type == sf::Event::Closed) window.close(); // ���� ����� �������, ��������� ����

			if (!cmdActive) CMD::Key(shapes, event, focus, typeFigure[idFigure]); // ���� ������� ���������, ����� ���� � ����������
			else CMD::Text(shapes, cmd, event, focus); // ����� ����� ���� � ���������� � ��������� �������

			if (time >= CMD::TIME) {
				if (Keyboard::isKeyPressed(Keyboard::Key::Tilde)) { // ������������ ������� �� "������"
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
				}
				time = 0.f;
			}
		}

		window.clear(); // ������ ���� ����� ���������� ������ �����
		for (auto i = 0; i < shapes.size(); i++) {
			//ShapeDealer::ObstacleScale(shapes, i); // ��������� ������������ �����
			ShapeDealer::Draw(dynamic_cast<IDraw*>(shapes[i]), window); // ������ ������
			if (coordinateActive && std::find(focus.begin(), focus.end(), i) != focus.end()) ShapeDealer::DrawPosition(shapes[i], window);
		}

		if (!shapes.empty() && !focus.empty()) camera.setCenter(shapes[focus[0]]->GetPosition().GetX(),
																shapes[focus[0]]->GetPosition().GetY());
		// ������ ������, � ������� ����������� ������
		TextDisplay(window, camera, cmd, cmdActive, typeFigure[idFigure]); // ������� �����
		if (tip) Tip(window, camera);

		window.setView(camera); // ������������� ������
		window.display(); // ��������� ����
	}
}
