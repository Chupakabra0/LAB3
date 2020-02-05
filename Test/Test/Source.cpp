#include <GLFW/glfw3.h>
#include <cstdlib>
#include "Point.h"
#include <iostream>
#define WINDOW

void output(Point* point) {
	std::cout << "X: " << point->GetPosition().getX() << " Y: " << point->GetPosition().getY() << std::endl;
}

int main(void) {

	Point first(100.f, 100.f);

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
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		/* Swap front and back buffers */
		glBegin(GL_POINTS); //TODO make class-method
			glColor3f(0.1f, 0.6f, 0);
			glVertex2f(first.GetPosition().getX() / 1000, first.GetPosition().getY() / 1000); //TODO remove /1000
		glEnd();
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
#endif

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
