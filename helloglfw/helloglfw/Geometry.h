#pragma once
#include <string>

struct color
{
	float red;
	float green;
	float blue;
};

class Geometry
{
private:
	int center_x_, center_y_, radius_, thickness_;
	int state_;
	color object_color_;
	color backround_color_;
	const int num_segments = 1000;
	const int width = 640;
	const int height = 480;

public:
	float* tempPixels = new float[width * height * 3];

	Geometry()
	{
		backround_color_.red = 1.0f;
		backround_color_.green = 1.0f;
		backround_color_.blue = 1.0f;

		object_color_.red = 1.0f;
		object_color_.green = 0.0f;
		object_color_.blue = 0.0f;
	}

	virtual void setInit(const int& _center_x, const int& _center_y, const int& _radius, const int& _thickness) = 0;

	void clearBackgroundColor(float* pixels);

	virtual void draw(float* pixels) = 0;

	static Geometry* createGeometry(std::string& name);
	
	void drawOnePixel(const int& i, const int& j, float* pixels);

	void setColor(const float& r, const float& g, const float& b);

	void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, float* pixels);

	void findInner(const double& x, const double& y, float* pixels);

	//box
	void initialize(const int& _cx, const int& _cy, const int& _half_size, float* pixels);

	//circle
	void initialize(const int& _cx, const int& _cy, const int& _r, const int& thickness, float* pixels);
};