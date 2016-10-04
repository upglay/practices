#include <GLFW/glfw3.h>
#include <stdbool.h>
#include "Geometry.h"
#include "Global.h"
#include "Square.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"
#include <math.h>
#include <vector>
#include <iostream>

int main(void)
{
	GLFWwindow* window;

	std::vector<Geometry*> geo_vector;

	geo_vector.push_back(Geometry::createGeometry(std::string("Circle")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Square")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Triangle")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Polygon")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Polygon")));
	geo_vector.push_back(Geometry::createGeometry(std::string("Polygon")));
	
	//drawing red circle(in mother class only once)
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			int pos = i + (3 * j);
			geo_vector[pos]->initialize(100 + 200 * i, 160 * (j + 1), 75, 3);
		}
	}

	Circle *temp = (Circle*)geo_vector[0];
	temp->init(100 + 200*0, 160*1, 45, 5);

	Square *temp1 = (Square*)geo_vector[1];
	temp1->init(100 + 200*1, 160*1, 45, 5);

	Triangle *temp2 = (Triangle*)geo_vector[2];
	temp2->init(100 + 200 * 2, 160 * 1, 45, 5);
	
	Polygon* temp3;
	for (int i = 0; i < 3; i++)
	{
		temp3 = (Polygon*)geo_vector[3 + i];
		temp3->init(100 + 200 * i, 160 * 2, 45, 5, 5+i);
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

	geo_vector[0]->clearBackgroundColor();
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetCursorPos(window, &win_x, &win_y);

		for (auto itr : geo_vector)
		{
			(itr)->findInner(win_x, height - win_y);
			(itr)->draw();

		}
			
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;

	return 0;
}

Geometry* Geometry::createGeometry(std::string& name)
{
	if (name == "Circle")
	{
		return new Circle();
	}
	else if (name == "Square")
	{
		return new Square();
	}
	else if (name == "Triangle")
	{
		return new Triangle();
	}
	else if (name == "Polygon")
	{
		return new Polygon();
	}
}