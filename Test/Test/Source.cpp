#include <GLFW/glfw3.h>
#include <cstdlib>
#include "Point.h"
#include <iostream>
//#define WINDOW

void output(Point* point) {
	std::cout << "X: " << point->getPosition().getX() << " Y: " << point->getPosition().getY() << std::endl;
}

int main(void) {

#ifdef WINDOW 
  	/* Initialize the library */
	if (!glfwInit()) throw "Lib isn`t working!";

	/* Create a windowed mode window and its OpenGL context */
	const auto window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		throw "Window isn`t working!";
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
#endif

	Point first(1.f, 1.f);
	std::cout << "First: ";
	output(&first);

	std::cout << "+(1.f; 2.f)";
	first.ChangePosition(1.f, 2.f);
	output(&first);

	std::cout << "=(0.f; 0.f)";
	first.SetPosition(0.f, 0.f);
	output(&first);

	std::cout << "Previous: ";
	first.PreviousPosition();
	output(&first);

	system("pause > NUL");
	return EXIT_SUCCESS;
}
