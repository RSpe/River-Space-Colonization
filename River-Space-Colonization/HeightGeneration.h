#pragma once

#include "Include.h"

class HeightGeneration
{
public:
	static const std::vector<float> create_base_heights(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour);
private:
};
