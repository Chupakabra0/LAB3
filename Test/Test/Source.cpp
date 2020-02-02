#include <GLFW/glfw3.h>
#include <cstdlib>

int main(void) {

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
	return EXIT_SUCCESS;
}
