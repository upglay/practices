#pragma once
#include "Global.h"

struct color
{
	float red;
	float green;
	float blue;
};

class Geometry
{
private:
	int center_x_, center_y_, radius_;
	int state_;
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

	void clearBackgroundColor()
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

	virtual void draw() = 0;

	static Geometry* createGeometry(std::string& name);
	
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

	void findInner(const double& x, const double& y)
	{
		if (state_ == 1)
		{
			if ((x <= center_x_ + (radius_ / 2)) && (x >= center_x_ - (radius_ / 2)) && (y <= center_y_ + (radius_ / 2)) && (y >= center_y_ - (radius_ / 2)))
			{
				setColor(0.0f, 0.0f, 1.0f);
				initialize(center_x_, center_y_, radius_ / 2);
			}
			else
			{
				setColor(1.0f, 0.0f, 0.0f);
				initialize(center_x_, center_y_, radius_ / 2);
			}
		}	
		else if (state_ == 2)
		{
			float dis = (center_x_ - x)*(center_x_ - x) + (center_y_ - y)*(center_y_ - y);
			if (dis <= radius_*radius_)
			{
				setColor(0.0f, 0.0f, 1.0f);
				initialize(center_x_, center_y_, radius_, 3);
			}
			else
			{
				setColor(1.0f, 0.0f, 0.0f);
				initialize(center_x_, center_y_, radius_, 3);
			}
		}
	}

	//box
	void initialize(const int& _cx, const int& _cy, const int& _half_size)
	{
		state_ = 1;
		center_x_ = _cx;
		center_y_ = _cy;
		radius_ = _half_size * 2;

		drawLine(center_x_ - (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ + (radius_ / 2));
		drawLine(center_x_ + (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ - (radius_ / 2));
		drawLine(center_x_ + (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ - (radius_ / 2));
		drawLine(center_x_ - (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ + (radius_ / 2));
	}

	//circle
	void initialize(const int& _cx, const int& _cy, const int& _r, const int& thickness)
	{
		state_ = 2;
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