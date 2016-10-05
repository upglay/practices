#include <GLFW/glfw3.h>
#include "Geometry.h"
#include <vector>
#include <iostream>

const int width = 640;
const int height = 480;

float* pixels = new float[width * height * 3];

int main(void)
{
	GLFWwindow* window;
	double win_x, win_y;

	std::vector<Geometry*> geo_vector;

	geo_vector.push_back(Geometry::createGeometry(std::string("Circle")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Square")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Triangle")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Polygon_5")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Polygon_6")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Polygon_14")));
	
	//drawing red circle(in mother class only once)
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			int pos = i + (3 * j);
			geo_vector[pos]->initialize(100 + 200 * i, 160 * (j + 1), 75, 5, pixels);
			geo_vector[pos]->setInit(100 + 200 * i, 160 * (j + 1), 45, 3);
		}
	}

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	geo_vector[0]->clearBackgroundColor(pixels);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetCursorPos(window, &win_x, &win_y);

		for (auto itr : geo_vector)
		{
			(itr)->findInner(win_x, height - win_y, pixels);
			(itr)->draw(pixels);
		}
			
		glDrawPixels(640, 480, GL_RGB, GL_FLOAT, pixels);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

