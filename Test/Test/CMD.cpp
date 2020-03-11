#include "CMD.h"
#include <sstream>
#include <algorithm>
#include "Agregat.h"

float CMD::SPEED                   = 800.f;
float CMD::MOVE                    = 1.f;
float CMD::ROTATE                  = 0.1f;
float CMD::SCALE_PLUS              = 1.f;
float CMD::SCALE_MINUS             = -SCALE_PLUS;
								   
const std::string CMD::SET	       = "Set";
const std::string CMD::CREATE      = "Create";
const std::string CMD::SWITCH      = "Switch";
const std::string CMD::POSITION    = "Position";
const std::string CMD::ANGLE       = "Angle";
const std::string CMD::COLOR       = "Color";
const std::string CMD::SCALE       = "Scale";
const std::string CMD::FOCUS       = "Focus";
const std::string CMD::DELETE      = "Delete";
const std::string CMD::VISIBLE     = "Visible";
const std::string CMD::TRACE       = "Trace";
const std::string CMD::DOWN		   = "Down";
const std::string CMD::UP		   = "Up";
const std::string CMD::ALL         = "All";

const std::string CMD::SPEED_TEXT  = "Speed";
const std::string CMD::MOVE_TEXT   = "Move";
const std::string CMD::ROTATE_TEXT = "Rotate";
const std::string CMD::SCALE_TEXT  = "Scale";

const std::string CMD::X           = "X";
const std::string CMD::Y           = "Y";

const std::string CMD::AGREGAT     = to_string(figureID::AGREGAT);
const std::string CMD::CIRCLE      = to_string(figureID::CIRCLE);

std::string to_string(figureID id) {
	switch (id) {
	case CIRCLE: return typeid(Circle).name() + std::string("class ").size();
	case AGREGAT : return typeid(Agregat).name() + std::string("class ").size();
	default: return "unknown";
	}
}

void CMD::Key(std::vector<Figure*>& shapes, Event& event, std::vector<unsigned>& focus, figureID& id) {
	if (!shapes.empty() && event.type == Event::KeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			for (auto element : focus) ShapeDealer::Move(dynamic_cast<IMove*>(shapes[element]), XY(-MOVE, 0.f));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
			for (auto element : focus) ShapeDealer::Move(dynamic_cast<IMove*>(shapes[element]), XY(MOVE, 0.f));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
			for (auto element : focus) ShapeDealer::Move(dynamic_cast<IMove*>(shapes[element]), XY(0.f, -MOVE));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
			for (auto element : focus) ShapeDealer::Move(dynamic_cast<IMove*>(shapes[element]), XY(0.f, MOVE));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::E)) {
			for (auto element : focus) ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[element]), Angle(-ROTATE));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
			for (auto element : focus) ShapeDealer::Rotate(dynamic_cast<IRotate*>(shapes[element]), Angle(ROTATE));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
			for (auto element : focus) ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[element]), Scale(SCALE_PLUS));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
			for (auto element : focus) ShapeDealer::Zoom(dynamic_cast<IScale*>(shapes[element]), Scale(SCALE_MINUS));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Z)) {
			for (auto element : focus) ShapeDealer::LegacyCondition(dynamic_cast<IMove*>(shapes[element]));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::X)) {
			for (auto element : focus) ShapeDealer::FirstCondition(dynamic_cast<IMove*>(shapes[element]));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::V)) {
			for (auto element : focus) ShapeDealer::SwitchVisible(dynamic_cast<Figure*>(shapes[element]));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::C)) {
			for (auto element : focus) ShapeDealer::SwitchTrace(dynamic_cast<Figure*>(shapes[element]));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::PageDown)) {
			//for (auto element : focus) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));

			//if (focus.size() > 1) focus.erase(focus.begin() + 1, focus.end());

			//if (focus[0] != 0) focus[0]--;
			//else focus[0] = shapes.size() - 1;
			//ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0]]));
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::PageUp)) {
			//for (auto element : focus) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));

			//if (focus.size() > 1) focus.erase(focus.begin() + 1, focus.end());

			//if (focus[0] != shapes.size() - 1) focus[0]++;
			//else focus[0] = 0;
			//ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0]]));
		}
	}
	else if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::Key::Add) {
			std::vector<unsigned> coordinates;
			CreateFigure(shapes, coordinates, focus, id);
		}
		if (event.key.code == Keyboard::Key::Subtract) {
			DeleteFigure(shapes, focus);
		}
	}
}

void CMD::Text(std::vector<Figure*>& shapes, std::string& string, const Event& event, std::vector<unsigned>& focus) {
	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode == '\b') {
			if (!string.empty()) string.erase(string.cend() - 1);
		}
		else if (event.text.unicode == 13) Check(shapes, string, focus);
		else if (event.text.unicode != 43 && event.text.unicode != 96 && event.text.unicode != 1105) string += {
			static_cast<char>(event.text.unicode)
		};
	}
}

void CMD::Check(std::vector<Figure*>& shapes, std::string& string, std::vector<unsigned>& focus) {
	if (string.find(CREATE, 0) != -1) {
		if (string.find(CIRCLE, 0) != -1) {
			auto coordinates = Convert(string);
			CreateFigure(shapes, coordinates, focus, figureID::CIRCLE);
		}
		else if (string.find(AGREGAT, 0) != -1) {
			auto coordinates = Convert(string);
			CreateFigure(shapes, coordinates, focus, figureID::AGREGAT);
		}
	}
	else if (string.find(SET, 0) != -1) {
		if (!shapes.empty()) {
			if (string.find(POSITION, 0) != -1) {
				auto coordinates = Convert(string);
				for (auto element : focus) SetFigurePosition(dynamic_cast<IMove*>(shapes[element]), coordinates);
			}
			else if (string.find(ANGLE, 0) != -1) {
				auto coordinates = Convert(string);
				for (auto element : focus) SetFigureAngle(dynamic_cast<IRotate*>(shapes[element]), coordinates);
			}
			else if (string.find(COLOR, 0) != -1) {
				auto coordinates = Convert(string);
				for (auto element : focus) SetFigureColor(dynamic_cast<IDraw*>(shapes[element]), coordinates);
			}
			else if (string.find(SCALE, 0) != -1) {
				if (string.find(X, 0) != -1) {
					auto coordinates = Convert(string);
					for (auto element : focus) SetFigureScaleX(dynamic_cast<IScale*>(shapes[element]), coordinates);
				}
				else if (string.find(Y, 0) != -1) {
					auto coordinates = Convert(string);
					for (auto element : focus) SetFigureScaleY(dynamic_cast<IScale*>(shapes[element]), coordinates);
				}
				else {
					auto coordinates = Convert(string);
					for (auto element : focus) SetFigureScale(dynamic_cast<IScale*>(shapes[element]), coordinates);
				}
			}
			else if (string.find(FOCUS, 0) != -1) {
				auto coordinates = Convert(string);
				SetFigureFocus(shapes, coordinates, focus);
			}
		}

		if (string.find(SPEED_TEXT, 0) != -1) {
			auto coordinates = Convert(string);
			if (!coordinates.empty()) ConstantSetter(SPEED, coordinates[0]);
		}
		else if (string.find(MOVE_TEXT, 0) != -1) {
			auto coordinates = Convert(string);
			if (!coordinates.empty()) ConstantSetter(MOVE, coordinates[0]);
		}
		else if (string.find(ROTATE_TEXT, 0) != -1) {
			auto coordinates = Convert(string);
			if (!coordinates.empty()) ConstantSetter(ROTATE, coordinates[0]);
		}
		else if (string.find(SCALE_TEXT, 0) != -1) {
			auto coordinates = Convert(string);
			if (!coordinates.empty()) {
				ConstantSetter(SCALE_PLUS, coordinates[0]);
				ConstantSetter(SCALE_MINUS, -SCALE_PLUS);
			}
		}
	}
	else if (string.find(DELETE, 0) != -1) {
		if (string.find(ALL, 0) != -1) {
			DeleteFigure(shapes);
			focus.erase(focus.begin(), focus.end());
			focus.push_back(0);
		}
		else {
			auto coordinates = Convert(string);
			if (coordinates.empty()) DeleteFigure(shapes, focus);
			else DeleteFigure(shapes, coordinates, focus);
		}
	}
	else if (string.find(SWITCH, 0) != - 1) {
		if (!shapes.empty()) {
			if (string.find(TRACE, 0) != -1) {
				if (string.find(ALL) != -1) {
					SetFigureTrace(shapes);
				}
				else {
					auto coordinates = Convert(string);
					if (coordinates.empty()) {
						for (auto element : focus) SetFigureTrace(shapes, element);
					}
					else SetFigureTrace(shapes, coordinates);
				}
			}
			else if (string.find(VISIBLE, 0) != -1) {
				auto coordinates = Convert(string);
				if (!coordinates.empty()) SetFigureVisible(shapes, coordinates);
				else for (auto element : focus) SetFigureVisible(shapes, element);
			}
			else if (string.find(FOCUS, 0) != -1) {
				if (string.find(UP, 0) != -1) {
					for (auto element : focus) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));

					if (focus.size() > 1) focus.erase(focus.begin() + 1, focus.end());

					if (focus[0] != shapes.size() - 1) focus[0]++;
					else focus[0] = 0;
					ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0]]));
				}
				else if (string.find(DOWN, 0) != -1) {
					for (auto element : focus) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));

					if (focus.size() > 1) focus.erase(focus.begin() + 1, focus.end());

					if (focus[0] != 0) focus[0]--;
					else focus[0] = shapes.size() - 1;
					ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0]]));
				}
			}
		}
	}
	string.erase();
}

std::vector<unsigned> CMD::Convert(std::string& string) {
	string = NumberCheck(string);
	std::replace(string.begin(), string.end(), '_', ' ');
	std::istringstream ss(string);
	return std::vector<unsigned>{std::istream_iterator<unsigned>(ss), {}};
}

std::string CMD::NumberCheck(std::string& string) {
	std::string result;
	const auto size = string.size();
	for (auto i = 0; i < size; i++) {
		if (string[i] == '_' || (string[i] >= '0' && string[i] <= '9') || string[i] == '-') {
			result += string[i];
		}
	}
	return result;
}

void CMD::CreateFigure(std::vector<Figure*>& shapes, std::vector<unsigned>& coordinates, std::vector<unsigned>& focus,
						figureID id) {
	if (!shapes.empty()) {
		for (auto element : focus) {
			ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));
		}
	}
	Figure* temp = nullptr;
	switch (id) {
	case figureID::AGREGAT: {
		vector<Figure*> vect;
		if (coordinates.empty()) {
			for (auto i = 0; i < shapes.size(); i++) {
				for (auto element : focus) {
					if (element == i) {
						vect.push_back(ShapeDealer::MakeCopy(shapes[i]));
						break;
					}
				}
			}
		}
		else {
			for (auto i = 0; i < shapes.size(); i++) {
				for (auto coordinate : coordinates) {
					if (coordinate == i) {
						vect.push_back(ShapeDealer::MakeCopy(shapes[i]));
						break;
					}
				}
			}
		}
		temp = new Agregat(vect);
		break;
	}
	case figureID::CIRCLE: {
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
	shapes.push_back(temp);
	focus[0] = shapes.size() - 1;
	ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0]]));
}

void CMD::SetFigurePosition(IMove* shape, std::vector<unsigned>& coordinates) {
	if (coordinates.size() > 1) ShapeDealer::SetPosition(shape, XY(coordinates[0], coordinates[1]));
	else if (coordinates.size() == 1) ShapeDealer::SetPosition(shape, XY(coordinates[0]));
}

void CMD::SetFigureAngle(IRotate* shape, std::vector<unsigned>& coordinates) {
	if (!coordinates.empty()) ShapeDealer::SetAngle(shape, Angle(coordinates[0]));
}

void CMD::SetFigureColor(IDraw* shape, std::vector<unsigned>& coordinates) {
	if (coordinates.size() > 3) ShapeDealer::SetColor(
		shape, Color(coordinates[0], coordinates[1], coordinates[2], coordinates[3]));
	else if (coordinates.size() == 3) ShapeDealer::SetColor(
		shape, Color(coordinates[0], coordinates[1], coordinates[2]));
}

void CMD::SetFigureScale(IScale* shape, std::vector<unsigned>& coordinates) {
	if (coordinates.size() > 1) ShapeDealer::SetScale(shape, Scale(XY(coordinates[0], coordinates[1])));
	else if (coordinates.size() == 1) ShapeDealer::SetScale(shape, Scale(coordinates[0]));
}

void CMD::SetFigureScaleX(IScale* shape, std::vector<unsigned>& coordinates) {
	if (!coordinates.empty()) ShapeDealer::SetScale(shape, Scale(XY(coordinates[0], 1.f)));
}

void CMD::SetFigureScaleY(IScale* shape, std::vector<unsigned>& coordinates) {
	if (!coordinates.empty()) ShapeDealer::SetScale(shape, Scale(XY(1.f, coordinates[0])));
}

void CMD::SetFigureFocus(std::vector<Figure*>& shapes,  vector<unsigned>& coordinates, std::vector<unsigned>& focus) {
	if (!coordinates.empty()) {
		for (auto element : focus) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));
		focus.erase(focus.begin(), focus.end());
		for (auto element : coordinates) {
			if (shapes.size() > element) {
				focus.push_back(element);
				ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[element]));
			}
		}
		if (focus.empty()) {
			focus.push_back(0);
			if (!shapes.empty()) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[0]));
		}
	}
}

void CMD::DeleteFigure(std::vector<Figure*>& shapes) {
	shapes.erase(shapes.begin(), shapes.end());
}

void CMD::DeleteFigure(std::vector<Figure*>& shapes, std::vector<unsigned>& focus) {
	if (!shapes.empty()) {
		for (auto element : focus) {
			shapes[element] = nullptr;
		}
		for (auto i = 0; i < shapes.size(); ) {
			if (shapes[i] == nullptr) shapes.erase(shapes.begin() + i);
			else i++;
		}
		focus[0] = 0;
		if (!shapes.empty()) ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0]]));
		focus.erase(focus.begin() + 1, focus.end());
	}
}

void CMD::DeleteFigure(std::vector<Figure*>& shapes, vector<unsigned>& coordinates, std::vector<unsigned>& focus) {
	if (!coordinates.empty() && shapes.size() > coordinates[0]) {
		ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[coordinates[0]]));
		shapes.erase(shapes.begin() + coordinates[0]);
		shapes.shrink_to_fit();
		if (focus[0] == coordinates[0]) {
			if (focus[0] != 0) {
				ShapeDealer::SwitchFocus(dynamic_cast<Figure*>(shapes[focus[0] - 1]));
			}
			else if (!shapes.empty()) focus[0] = shapes.size() - 1;
		}
		else {
			focus[0]--;
		}
		focus.erase(focus.begin() + 1, focus.end());
	}
}

void CMD::SetFigureVisible(std::vector<Figure*>& shapes, vector<unsigned>& coordinates) {
	if (!coordinates.empty() && shapes.size() > coordinates[0]) ShapeDealer::SwitchVisible(shapes[coordinates[0]]);
}

void CMD::SetFigureVisible(std::vector<Figure*>& shapes, unsigned& focus) {
	if (!shapes.empty()) ShapeDealer::SwitchVisible(shapes[focus]);
}

void CMD::SetFigureTrace(std::vector<Figure*>& shapes, vector<unsigned>& coordinates) {
	if (!coordinates.empty() && shapes.size() > coordinates[0]) ShapeDealer::SwitchTrace(shapes[coordinates[0]]);
}

void CMD::SetFigureTrace(std::vector<Figure*>& shapes, unsigned& focus) {
	if (!shapes.empty()) ShapeDealer::SwitchTrace(shapes[focus]);
}

void CMD::SetFigureTrace(std::vector<Figure*>& shapes) {
	const auto size = shapes.size();
	for (unsigned i = 0; i < size; i++) {
		SetFigureTrace(shapes, i);
	}
}

void CMD::ConstantSetter(float& value, const float& coordinates) {
	value = coordinates;
}