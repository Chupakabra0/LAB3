#include <string>
#include "Interfaces.h"

std::string to_string(Color color) {
	switch (color) {
	case BLACK: return static_cast<std::string>("Black");
	case BLUE: return static_cast<std::string>("Blue");
	case GREEN: return static_cast<std::string>("Green");
	case CYAN: return static_cast<std::string>("Cyan");
	case RED: return static_cast<std::string>("Red");
	case MAGENTA: return static_cast<std::string>("Magenta");
	case BROWN: return static_cast<std::string>("Brown");
	case LIGHTGRAY: return static_cast<std::string>("Light gray");
	case DARKGRAY: return static_cast<std::string>("Dark gray");
	case LIGHTBLUE: return static_cast<std::string>("Light blue");
	case LIGHTGREEN: return static_cast<std::string>("Light green");
	case LIGHTCYAN: return static_cast<std::string>("Light cyan");
	case LIGHTRED: return static_cast<std::string>("Light red");
	case LIGHTMAGENTA: return static_cast<std::string>("Light magenta");
	case YELLOW: return static_cast<std::string>("Yellow");
	case WHITE: return static_cast<std::string>("White");
	default: return static_cast<std::string>("Unknown");
	}
}