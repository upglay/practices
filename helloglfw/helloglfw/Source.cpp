#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

GLFWwindow* window;
double win_x, win_y;

const int width = 640;
const int height = 480;

// color = (Red, Green, Blue)
float* pixels = new float[width * height * 3];

void drawOnePixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width*j) * 3 + 0] = red;	//red
	pixels[(i + width*j) * 3 + 1] = green;	//green
	pixels[(i + width*j) * 3 + 2] = blue;	//blue
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 < i1)
	{
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawOnePixel(i, j, red, green, blue);
		}
	}
	else if (i0 > i1)
	{
		for (int i = i1; i <= i0; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawOnePixel(i, j, red, green, blue);
		}
	}
	else
	{
		if (j0 < j1)
		{
			for (int j = j0; j < j1; j++)
			{
				drawOnePixel(i0, j, red, green, blue);
			}
		}
		else if (j0 > j1)
		{
			for (int j = j1; j < j0; j++)
			{
				drawOnePixel(i0, j, red, green, blue);
			}
		}
		else
		{
			drawOnePixel(i0, j0, red, green, blue);
		}
	}


}

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


bool measurement(const float cx, const float cy, const float r, const float x_cur, const float y_cur)
{
	return (cx - (float)x_cur)*(cx - (float)x_cur) + (cy - (float)y_cur)*(cy - (float)y_cur) - r*r < 0.0;
}

void DrawCircle(float cx, float cy, float r, int num_segments, bool significant)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;
	float rgb_red, rgb_green, rgb_blue;
	rgb_red = 1.0f; rgb_green = 0.0f; rgb_blue = 0.0f;

	float x = r;//we start at angle = 0 
	float y = 0;

	if (measurement(cx, cy, r, win_x, height - win_y) && significant) {
		rgb_red = 0.0f; rgb_green = 0.0f; rgb_blue = 1.0f;
	}

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		//glVertex2f(x + cx, y + cy);//output vertex 
		drawPixel(x + cx, y + cy, rgb_red, rgb_green, rgb_blue);

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}


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

void drawCircle(const int& x, const int& y, const int& radius, const float& red, const float& green, const float& blue)
{
	if (radius <= 0)
		return;

	int xK = 0;
	int yK = radius;
	int pK = 3 - (radius + radius);

	do {
		drawSquareFill(x + xK, y - yK, x + xK + 4, y - yK + 4, red, green, blue);

		drawSquareFill(x - xK, y - yK, x - xK + 4, y - yK + 4, red, green, blue);

		drawSquareFill(x + xK, y + yK, x + xK + 4, y + yK + 4, red, green, blue);

		drawSquareFill(x - xK, y + yK, x - xK + 4, y + yK + 4, red, green, blue);

		drawSquareFill(x + yK, y - xK, x + yK + 4, y - xK + 4, red, green, blue);

		drawSquareFill(x + yK, y + xK, x + yK + 4, y + xK + 4, red, green, blue);

		drawSquareFill(x - yK, y - xK, x - yK + 4, y - xK + 4, red, green, blue);

		drawSquareFill(x - yK, y + xK, x - yK + 4, y + xK + 4, red, green, blue);


		xK++;

		if (pK < 0)
		{
			pK += (xK << 2) + 6;
		}
		else
		{
			--yK;
			pK += ((xK - yK) << 2) + 10;
		}
	} while (xK <= yK);
}

void draw()
{
	const int i_center = 50;
	const int j_center = 50;
	const int thickness = 10;

	for (int i = 0; i < thickness; i++)
	{
		drawLine(40 + i, 300, 140 + i, 400, 0, 1, 0);
	}

	drawSquare(280, 300, 380, 400, 0, 0, 1);

	drawSquareFill(500, 300, 600, 400, 1, 0, 0);

	drawTriangle(90, 200, 140, 100, 40, 100, 1, 0, 0);

	drawPentagon(280, 150, 330, 200, 380, 150, 355, 100, 305, 100, 1, 0, 0);

	drawCircle(550, 150, 50, 0, 0, 0);

}

// dynamic memory allocation in c 
// flaot* pixels = (float*)malloc(sizeof(float)*width*height*3);

int main(void)
{
	GLFWwindow* window;

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

		// white background color
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				pixels[(i + width*j) * 3 + 0] = 1.0f;	//red
				pixels[(i + width*j) * 3 + 1] = 1.0f;	//green
				pixels[(i + width*j) * 3 + 2] = 1.0f;	//blue
			}

		draw();

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