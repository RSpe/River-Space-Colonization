#pragma once

#include <fstream>

#include "Include.h"
#include "Branch.h"

class HeightGeneration
{
public:
	void generate_heights(int window_width, int window_height, int max_x_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour, int tree_number);

	void write_pgm_height_map(int max_x_point, int max_y_point);
	void show_feature_map(std::vector<std::vector<float>>, int max_x_point);
	void curve_primative(int max_x_point, int max_y_point);
	void set_curve_height(int x_location, int y_location, int new_x, int new_y, float max_distance, int max_x_point, float river_height);

	std::vector<std::vector<float>> get_feature_map();

	int primative_distance = 10;
	float angle_multiplier = 0.5f;

private:
	std::vector<std::vector<float>> feature_map;

	//float blend_height(float max_distance, float distance);
};

