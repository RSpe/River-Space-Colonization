#pragma once

#include "Include.h"

class HeightGeneration
{
public:
	void generate_maps(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour);

	std::vector<float> get_height_map();
	std::vector<glm::vec2> get_location_map();
private:
	std::vector<float> height_map;
	std::vector<glm::vec2> location_map;
};

