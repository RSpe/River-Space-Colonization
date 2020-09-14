#include "HeightGeneration.h"

#define _USE_MATH_DEFINES
#include <math.h>

void HeightGeneration::generate_maps(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour, int tree_number)
{
	
	int read_point_x = (window_width / 2) - (max_x_point / 2);
	int read_point_y = (window_height / 2) - (max_y_point / 2);

	for (float i = read_point_y; i < read_point_y + max_y_point; ++i)
	{
		float y_coord = 2 * ((i - 0) / (window_height - 0)) - 1;
		for (float j = read_point_x; j < read_point_x + max_x_point; ++j)
		{
			float x_coord = 2 * ((j - 0) / (window_width - 0)) - 1;
			location_map.push_back(glm::vec2(x_coord, y_coord));
		}
	}

	glReadBuffer(GL_FRONT);

	int rgb_count = 4 * max_x_point * max_y_point;

	std::vector<GLfloat> colours(rgb_count);

	glReadPixels(read_point_x, read_point_y, max_x_point, max_y_point, GL_RGBA, GL_FLOAT, colours.data());

	for (int n = 0; n != max_y_point / 2; ++n) 
	{
		std::swap_ranges(colours.begin() + 4 * max_x_point * n, colours.begin() + 4 * max_x_point * (n + 1), colours.begin() + 4 * max_x_point * (max_y_point - n - 1));
	}

	int x_count = 0;
	int y_count = 0;

	// Get the features and their heights, ridge = -3, river = -2, land/terrain = -1
	for (int m = 0; m < colours.size(); m += 4)
	{
		
		if (colours[m + 1] == 1.0f && colours[m] > 0.0f && colours[m] < 1.0f)
		{
			feature_map.push_back({ -3.0f, (1 - colours[m + 3]), 0.0f });
		}
		else if (colours[m + 3] != 1.0f)
		{
			feature_map.push_back({ -2.0f, (1 - colours[m + 3]), 0.0f });
			//std::cout << colours[m] << " " << colours[m + 1] << " " << colours[m + 2] << " " << colours[m + 3] << std::endl;
		}
		else 
		{
			feature_map.push_back({ -1.0f, 255.0f, 0.0f });
		}
	}
	curve_primative(max_x_point, max_y_point);
	//show_feature_map(feature_map, max_x_point);
}

void HeightGeneration::show_feature_map(std::vector<std::vector<float>> feature_map, int max_x_point)
{
	int next_line_count = 0;
	int y_value = 0;

	for (int j = 0; j < feature_map.size(); ++j)
	{
		if (next_line_count == max_x_point - 1)
		{
			//location_map[(y_value * max_x_point) + (max_x_point - 1)][2] = feature_map[j][1];
			
			if (feature_map[j][0] == -3.0f)
			{
				std::cout << "-" << std::endl;
				next_line_count = 0;
			}
			else if (feature_map[j][0] == -2.0f)
			{
				std::cout << feature_map[j][1] << std::endl;
				next_line_count = 0;
			}
			else if (feature_map[j][1] > 0.0f)
			{
				std::cout << ">" << std::endl;
				next_line_count = 0;
			}
			else
			{
				std::cout << "0" << std::endl;
				next_line_count = 0;
			}
			y_value += 1;
		}
		else
		{
			//location_map[(y_value * max_x_point) + (j % max_x_point)][2] = feature_map[j][1];

			if (feature_map[j][0] == -3.0f)
			{
				std::cout << "-" << " ";
				next_line_count += 1;
			}
			else if (feature_map[j][0] == -2.0f)
			{
				std::cout << feature_map[j][1] << " ";
				next_line_count += 1;
			}
			else if (feature_map[j][1] > 0.0f)
			{
				std::cout << ">" << " ";
				next_line_count += 1;
			}
			else
			{
				std::cout << "0" << " ";
				next_line_count += 1;
			}
		}
	}
}

void HeightGeneration::curve_primative(int max_x_point, int max_y_point)
{	
	float max_distance = sqrt(pow(primative_distance, 2) + pow(primative_distance, 2));

	for (int i = 0; i < feature_map.size(); ++i)
	{
		if (feature_map[i][0] == -2.0f)
		{
			int x_location = i % max_x_point;
			int y_location = i / max_x_point;

			//std::cout << feature_map[i][1] << std::endl;
	
			float river_height = feature_map[i][1];
			//std::cout << feature_map[i][1] << std::endl;

			//std::cout << river_height << "  " << river_angle << std::endl;

			for (int y = -primative_distance; y <= primative_distance; ++y)
			{
				for (int x = -primative_distance; x <= primative_distance; ++x)
				{
					if ((x == 0 && y == 0))
					{
						continue;
					}

					int new_x = x_location + x;
					int new_y = y_location + y;

					if ((new_x > 0 && new_y > 0 && new_x < max_x_point && new_y < max_y_point))
					{ 
						set_curve_height(x_location, y_location, new_x, new_y, max_distance, max_x_point, river_height);
					}
				}
			}
		}
	}
}

void HeightGeneration::set_curve_height(int x_location, int y_location, int new_x, int new_y, float max_distance, int max_x_point, float river_height)
{
	float distance = sqrt(pow(new_x - x_location, 2) + pow(new_y - y_location, 2));
	float river_angle = atan((distance / river_height)) * angle_multiplier; // Radians
	float cross_section_height = tan(river_angle) * distance;

	//std::cout << river_height << " " << cross_section_height << std::endl;

	float type = feature_map[((new_y * max_x_point) + new_x)][0];
	float current_height = feature_map[((new_y * max_x_point) + new_x)][1];
	float current_weight = feature_map[((new_y * max_x_point) + new_x)][2];
	//std::cout << distance << std::endl;

	float point_elevation = (river_height * 255) + cross_section_height;
	float new_weight = pow((1 - pow((distance / max_distance), 2)), 3);

	//if (point_elevation > 255)
	//{
	//	std::cout << "warning" << " " << current_height << std::endl;

	//}

	//std::cout << river_height << std::endl;
	if (current_weight == 0.0f)
	{
		feature_map[((new_y * max_x_point) + new_x)][2] = new_weight;
	}
	
	if (type == -1.0f && current_weight == 0)
	{
		feature_map[((new_y * max_x_point) + new_x)][1] = point_elevation;
	}
	else if (type == -1.0f && current_weight > 0)
	{
		float weight = (distance / max_distance);
		feature_map[((new_y * max_x_point) + new_x)][1] = ((current_weight * current_height) + (new_weight * point_elevation)) / (current_weight + new_weight);
		feature_map[((new_y * max_x_point) + new_x)][1] = (current_height + point_elevation) / (2);
		feature_map[((new_y * max_x_point) + new_x)][1] = (current_height + (new_weight * point_elevation)) / (1 + new_weight);
		feature_map[((new_y * max_x_point) + new_x)][1] = (current_height + point_elevation) / 2;
	}
}

std::vector<std::vector<float>> HeightGeneration::get_feature_map()
{
	return feature_map;
}

std::vector<glm::vec2> HeightGeneration::get_location_map()
{
	return location_map;
}