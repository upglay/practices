#include <GLFW/glfw3.h>

const int width = 640;
const int height = 480;

// color = (Red, Green, Blue)
float* pixels = new float[ width * height * 3];

void drawOnePixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width*j) * 3 + 0] = red;	//red
	pixels[(i + width*j) * 3 + 1] = green;	//green
	pixels[(i + width*j) * 3 + 2] = blue;	//blue
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawOnePixel(i, j, red, green, blue);
	}
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