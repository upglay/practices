#pragma once

class Circle : public Geometry
{
private:
	int center_x_, center_y_, radius_, thickness_;
	const int num_segments = 1000;

public:
	Circle()
	{}

	Circle(const int& _center_x, const int& _center_y, const int& _radius, const int& _thickness)
		:center_x_(_center_x), center_y_(_center_y), radius_(_radius), thickness_(_thickness)
	{}

	void init(const int& _center_x, const int& _center_y, const int& _radius, const int& _thickness)
	{
		center_x_ = _center_x;
		center_y_ = _center_y;
		radius_ = _radius;
		thickness_ = _thickness;
	}

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