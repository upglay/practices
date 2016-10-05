#pragma once

class Triangle : public Geometry
{
	int center_x_, center_y_, radius_, thickness_;

public:
	Triangle()
	{}

	Triangle(const int& _center_x, const int& _center_y, const int& _radius)
		:center_x_(_center_x), center_y_(_center_y), radius_(_radius)
	{}

	void setInit(const int& _center_x, const int& _center_y, const int& _radius, const int& _thickness)
	{
		center_x_ = _center_x;
		center_y_ = _center_y;
		radius_ = _radius;
		thickness_ = _thickness;
	}

	void draw(float* pixels)
	{
		int x_pos_[3], y_pos_[3];

		float theta = 2 * 3.1415926 / 3;
		float c = cosf(theta);
		float s = sinf(theta);
		float t;

		float x = radius_;
		float y = 0;
		for (int i = 0; i < 3; i++)
		{
			x_pos_[i] = x + center_x_;
			y_pos_[i] = y + center_y_;

			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}

		drawLine(x_pos_[0], y_pos_[0], x_pos_[1], y_pos_[1], pixels);
		drawLine(x_pos_[2], y_pos_[2], x_pos_[1], y_pos_[1], pixels);
		drawLine(x_pos_[2], y_pos_[2], x_pos_[0], y_pos_[0], pixels);
	}
};