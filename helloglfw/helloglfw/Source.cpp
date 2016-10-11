#include <GLFW/glfw3.h>
#include "Geometry.h"
#include <vector>
#include <iostream>
#include "MyPainter2D.h"

MyPainter2D my_painter;

int main(void)
{
	my_painter.initialize();
	
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
			geo_vector[pos]->initialize(100 + 200 * i, 160 * (j + 1), 75, 5, my_painter.pixels);
			geo_vector[pos]->setInit(100 + 200 * i, 160 * (j + 1), 45, 3);
		}
	}

	geo_vector[0]->clearBackgroundColor(my_painter.pixels);
	
	

	/* Loop until the user closes the window */
	while(!my_painter.shouldCloseWindow())
	{
		
		my_painter.preprocessing();

		glfwGetCursorPos(my_painter.window, &win_x, &win_y);
		
		for (auto itr : geo_vector)
		{
			(itr)->findInner(win_x, my_painter.height - win_y, my_painter.pixels);
			(itr)->draw(my_painter.pixels);
		}
		
		my_painter.postprocessing();
	}

	glfwTerminate();

	return 0;
}

