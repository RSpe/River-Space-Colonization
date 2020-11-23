#pragma once

#define _USE_MATH_DEFINES

#include <fstream>
#include <math.h>

#include "Include.h"
#include "Branch.h"



class HeightGeneration
{
public:
	void generate_heights(int window_width, int window_height, int max_x_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour, int tree_number, double seed);

	void write_pgm_height_map(int max_x_point, int max_y_point);
	void show_feature_map(std::vector<std::vector<float>>, int max_x_point);
	void curve_primative(int max_x_point, int max_y_point, double seed);
	void set_curve_height(int x_location, int y_location, int new_x, int new_y, float max_distance, int max_x_point, float height, float ridge_angle_multiplier, int feature_type);

	std::vector<std::vector<float>> get_feature_map();

	int river_primative_distance = 13;
	float river_angle_multiplier = 80.0f * M_PI/180.0f; // 30 degrees to radians

	float ridge_height_mult = 0.9f;
	int ridge_primative_distance = 20;
	float ridge_angle_multiplier = 40.0f * M_PI / 180.0f; // 30 degrees to radians

private:
	std::vector<std::vector<float>> feature_map;

	float _max_x_point;
	float _max_y_point;

	float _river_min_distance;
	float _ridge_min_distance;
};

