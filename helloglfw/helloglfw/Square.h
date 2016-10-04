#pragma once
#include "Global.h"

class Square : public Geometry
{
private:
	int center_x_, center_y_, radius_;
	bool fill_ = true;

public:
	Square()
	{}

	Square(const int& _cx, const int& _cy, const int& _half_size)
		: center_x_(_cx), center_y_(_cy), radius_(_half_size * 2)
	{}

	void setFill(const bool& _fill)
	{
		fill_ = _fill;
	}

	void draw()
	{
		if (fill_)
		{
			for (int i = center_x_ - (radius_ / 2); i < center_x_ + (radius_ / 2); i++)
			{
				for (int j = center_y_ - (radius_ / 2); j < center_y_ + (radius_ / 2); j++)
				{
					drawOnePixel(i, j);
				}
			}
		}
		else
		{
			drawLine(center_x_ - (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ + (radius_ / 2));
			drawLine(center_x_ + (radius_ / 2), center_y_ + (radius_ / 2), center_x_ + (radius_ / 2), center_y_ - (radius_ / 2));
			drawLine(center_x_ + (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ - (radius_ / 2));
			drawLine(center_x_ - (radius_ / 2), center_y_ - (radius_ / 2), center_x_ - (radius_ / 2), center_y_ + (radius_ / 2));
		}
	}
};