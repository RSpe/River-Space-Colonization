#pragma once

#include "Include.h"
#include "Branch.h"

class HeightGeneration
{
public:
	void generate_maps(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour, int tree_number);

	void show_feature_map(std::vector<std::vector<float>>, int max_x_point);
	void curve_primative(int max_x_point, int max_y_point);
	void set_curve_height(int x_location, int y_location, int new_x, int new_y, float max_distance, int max_x_point);

	std::vector<std::vector<float>> get_feature_map();
	std::vector<glm::vec2> get_location_map();

	int primative_distance = 5;
	int degree = 90;

private:
	std::vector<std::vector<float>> feature_map;
	std::vector<glm::vec2> location_map;

	//float blend_height(float max_distance, float distance);
};

