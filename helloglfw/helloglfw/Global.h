#pragma once
#include "Geometry.h"
#include <math.h>
#include <string>

double win_x, win_y;

const int width = 640;
const int height = 480;

// color = (Red, Green, Blue)
float* pixels = new float[width * height * 3];