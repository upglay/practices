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
	Geometry **geo = new Geometry*[6];
	//for (int i = 0; i < 6; i++)
	//{
	//	geo[i] = new Square;
	//}
	
	geo[0]->clearBackgroundColor();

	std::vector<Geometry*> geo_vector;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			int pos = i + (3 * j);
			if (pos == 1)
			{
				geo_vector.push_back(new Square(100 + 200 * i, 160 * (j + 1), 20));
			}
			else if (pos == 2)
			{
				geo_vector.push_back(new Circle(100 + 200 * i, 160 * (j + 1), 20, 5));
			}
			else
			{
				geo_vector.push_back(new Polygon(100 + 200 * i, 160 * (j + 1), 20, pos + 3));
			}
			geo_vector[pos]->initialize(100 + 200 * i, 160 * (j + 1), 50);
		}
	}

	//for (int j = 0; j < 2; j++)
	//{
	//	for (int i = 0; i < 3; i++)
	//	{
	//		int pos = i + (3 * j);
	//		std::cout << pos << std::endl;
	//		if (pos < 2)
	//		{
	//			geo[pos] = new Square(100 + 200 * i, 160 * (j + 1), 20);
	//		}
	//		else if(pos >= 2 && pos < 4)
	//		{
	//			geo[pos] = new Circle(100 + 200 * i, 160 * (j + 1), 20, 5);
	//		}
	//		else
	//		{
	//			geo[pos] = new Triangle(100 + 200 * i, 160 * (j + 1), 20);
	//		}
	//		geo[pos]->initialize(100 + 200 * i, 160 * (j + 1), 50);
	//	}
	//}
	
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
			
		//for (int i = 0; i < 6; i++)
		//{
		//	geo[i]->findInner(win_x, height - win_y);
		//	geo[i]->draw();
		//}
			
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;
	delete geo;

	return 0;
}