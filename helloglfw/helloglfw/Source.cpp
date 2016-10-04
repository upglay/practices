#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

GLFWwindow* window;
double win_x, win_y;

const int width = 640;
const int height = 480;

// color = (Red, Green, Blue)
float* pixels = new float[width * height * 3];

struct color
{
	float red;
	float green;
	float blue;
};


class Geometry
{
private:
	float center_x_, center_y_, radius_;
	color object_color_;
	color backround_color_;
	const int num_segments = 1000;

public:
	Geometry()
	{
		backround_color_.red = 1.0f;
		backround_color_.green = 1.0f;
		backround_color_.blue = 1.0f;

		object_color_.red = 1.0f;
		object_color_.green = 0.0f;
		object_color_.blue = 0.0f;
	}

	void setBackgroundColor()
	{
		// white background color
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				pixels[(i + width*j) * 3 + 0] = 1.0f;	//red
				pixels[(i + width*j) * 3 + 1] = 1.0f;	//green
				pixels[(i + width*j) * 3 + 2] = 1.0f;	//blue
			}
	}

	virtual void draw()
	{}

	void drawOnePixel(const int& i, const int& j)
	{
		pixels[(i + width*j) * 3 + 0] = object_color_.red;	//red
		pixels[(i + width*j) * 3 + 1] = object_color_.green;	//green
		pixels[(i + width*j) * 3 + 2] = object_color_.blue;	//blue
	}

	void setColor(const float& r, const float& g, const float& b)
	{
		object_color_.red = r;
		object_color_.green = g;
		object_color_.blue = b;
	}

	void drawLine(const int& i0, const int& j0, const int& i1, const int& j1)
	{
		if (i0 < i1)
		{
			for (int i = i0; i <= i1; i++)
			{
				const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

				drawOnePixel(i, j);
			}
		}
		else if (i0 > i1)
		{
			for (int i = i1; i <= i0; i++)
			{
				const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

				drawOnePixel(i, j);
			}
		}
		else
		{
			if (j0 < j1)
			{
				for (int j = j0; j < j1; j++)
				{
					drawOnePixel(i0, j);
				}
			}
			else if (j0 > j1)
			{
				for (int j = j1; j < j0; j++)
				{
					drawOnePixel(i0, j);
				}
			}
			else
			{
				drawOnePixel(i0, j0);
			}
		}
	}

	//box
	void initialize(const int& _cx, const int& _cy, const int& _half_size)
	{
		center_x_ = _cx;
		center_y_ = _cy;
		radius_ = _half_size * 2;

		drawLine(center_x_ - (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ + (radius_ / 2));
		drawLine(center_x_ + (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ - (radius_ / 2));
		drawLine(center_x_ + (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ - (radius_ / 2));
		drawLine(center_x_ - (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ + (radius_ / 2));
	}

	//circle
	void initialize(const float& _cx, const float& _cy, const float& _r, const int& thickness)
	{
		
		center_x_ = _cx;
		center_y_ = _cy;
		radius_ = _r;

		float theta = 2 * 3.1415926 / float(num_segments);
		float c = cosf(theta);//precalculate the sine and cosine
		float s = sinf(theta);
		float t;

		float x = radius_;
		float y = 0;

		for (int i = 0; i < thickness; i++)
		{
			x = radius_ + i;
			y = 0;
			for (int ii = 0; ii < num_segments; ii++)
			{
				drawOnePixel(x + center_x_, y + center_y_);

				//apply the rotation matrix
				t = x;
				x = c * x - s * y;
				y = s * t + c * y;
			}
		}
	}
};

class Square : public Geometry
{
private:
	int center_x_, center_y_, radius_;
	
public:
	Square()
	{}

	Square(const int& _cx, const int& _cy, const int& _half_size)
		: center_x_(_cx), center_y_(_cy), radius_(_half_size * 2)
	{}

	void draw()
	{
		drawLine(center_x_ - (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ + (radius_ / 2));
		drawLine(center_x_ + (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ - (radius_ / 2));
		drawLine(center_x_ + (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ - (radius_ / 2));
		drawLine(center_x_ - (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ + (radius_ / 2));
	}
};


class Circle : public Geometry
{
	int center_x_, center_y_, radius_, thickness_;
	const int num_segments = 1000;

public:
	Circle()
	{}

	Circle(const int& _center_x, const int& _center_y, const int& _radius, const int& _thickness)
		:center_x_(_center_x), center_y_(_center_y), radius_(_radius), thickness_(_thickness)
	{}

	void draw()
	{

		float theta = 2 * 3.1415926 / float(num_segments);
		float c = cosf(theta);//precalculate the sine and cosine
		float s = sinf(theta);
		float t;

		float x = radius_;
		float y = 0;

		for (int i = 0; i < thickness_; i++)
		{
			x = radius_ + i;
			y = 0;
			for (int ii = 0; ii < num_segments; ii++)
			{
				drawOnePixel(x + center_x_, y + center_y_);

				//apply the rotation matrix
				t = x;
				x = c * x - s * y;
				y = s * t + c * y;
			}
		}
	}
};


class Arrow : public Geometry
{
public:
	Arrow()
	{}

	void draw()
	{}
};


/*
void drawSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i < i1; i++)
	{
		drawOnePixel(i, j0, red, green, blue);
		drawOnePixel(i, j1, red, green, blue);
	}
	for (int j = j0; j < j1; j++)
	{
		drawOnePixel(i1, j, red, green, blue);
		drawOnePixel(i0, j, red, green, blue);
	}
}

void drawSquareFill(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i < i1; i++)
		for (int j = j0; j < j1; j++)
			drawOnePixel(i, j, red, green, blue);
}

void drawTriangle(const int& i0, const int& j0, const int& i1, const int& j1, const int& i2, const int& j2, const float& red, const float& green, const float& blue)
{
	drawLine(i0, j0, i1, j1, red, green, blue);
	drawLine(i2, j2, i1, j1, red, green, blue);
	drawLine(i2, j2, i0, j0, red, green, blue);
}

void drawPentagon(const int& i0, const int& j0, const int& i1, const int& j1, const int& i2, const int& j2, const int& i3, const int& j3, const int& i4, const int& j4, const float& red, const float& green, const float& blue)
{
	drawLine(i0, j0, i1, j1, red, green, blue);
	drawLine(i1, j1, i2, j2, red, green, blue);
	drawLine(i3, j3, i2, j2, red, green, blue);
	drawLine(i4, j4, i3, j3, red, green, blue);
	drawLine(i0, j0, i4, j4, red, green, blue);
}
*/

int main(void)
{
	GLFWwindow* window;
	Geometry **geo = new Geometry*[10];
	for (int i = 0; i < 10; i++)
	{
		geo[i] = new Square;
	}
	
	geo[0]->setBackgroundColor();
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			int pos = i + (5 * j);
			if (j == 0)
			{
				geo[pos] = new Square(110 * (i + 1), 160 * (j + 1), 20);
			}
			else
			{
				geo[pos] = new Circle(110 * (i + 1), 160 * (j + 1), 20, 5);
			}
			geo[pos]->initialize(110 * (i + 1), 160 * (j + 1), 50, 3);
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

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetCursorPos(window, &win_x, &win_y);

		for (int i = 0; i < 10; i++)
			geo[i]->draw();

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