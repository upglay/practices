#pragma once

class Polygon : public Geometry
{
	int center_x_, center_y_, radius_, thickness_;
	int num_polygon_;

public:
	Polygon()
	{}

	Polygon(const int& _center_x, const int& _center_y, const int& _radius, const int& _num_polygon)
		:center_x_(_center_x), center_y_(_center_y), radius_(_radius), num_polygon_(_num_polygon)
	{}

	void init(const int& _center_x, const int& _center_y, const int& _radius, const int& _thickness, const int& _num_polygon)
	{
		center_x_ = _center_x;
		center_y_ = _center_y;
		radius_ = _radius;
		thickness_ = _thickness;
		num_polygon_ = _num_polygon;
	}

	void draw()
	{
		int *x_pos_ = (int*)malloc(sizeof(int)*num_polygon_);
		int *y_pos_ = (int*)malloc(sizeof(int)*num_polygon_);

		float theta = 2 * 3.1415926 / num_polygon_;
		float c = cosf(theta);
		float s = sinf(theta);
		float t;

		float x = radius_;
		float y = 0;
		for (int i = 0; i < num_polygon_; i++)
		{
			x_pos_[i] = x + center_x_;
			y_pos_[i] = y + center_y_;

			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}

		for (int i = 0; i < num_polygon_ - 1; i++)
		{
			drawLine(x_pos_[i], y_pos_[i], x_pos_[i + 1], y_pos_[i + 1]);
		}
		drawLine(x_pos_[num_polygon_ - 1], y_pos_[num_polygon_ - 1], x_pos_[0], y_pos_[0]);
	}
};