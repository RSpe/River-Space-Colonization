#include "HeightGeneration.h"


void HeightGeneration::generate_heights(int window_width, int window_height, int max_x_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour, int tree_number, double seed)
{
	_max_x_point = max_x_point;
	_max_y_point = max_y_point;

	float read_point_x = (window_width / 2.0f) - (max_x_point / 2.0f);
	float read_point_y = (window_height / 2.0f) - (max_y_point / 2.0f);

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
		if (colours[m] == ridge_colour[0] && colours[m + 1] == ridge_colour[1] && colours[m + 2] == ridge_colour[1])
		{
			feature_map.push_back({ -3.0f, colours[m + 3], 0.0f });
		}
		else if (colours[m + 3] != 1.0f)
		{
			feature_map.push_back({ -2.0f, colours[m + 3], 0.0f });
		}
		else 
		{
			feature_map.push_back({ -1.0f, 1.0f, -1.0f });
		}
	}
	curve_primative(max_x_point, max_y_point, seed);
	//show_feature_map(feature_map, max_x_point);
}

void HeightGeneration::write_pgm_height_map(int max_x_point, int max_y_point)
{
	std::ofstream height_map;

	height_map.open("height_map.pgm");

	height_map << "P2" << std::endl;
	height_map << max_x_point << " " << max_y_point << std::endl;
	height_map << 255 << std::endl;


	int current_line = 0;
	for (int i = 0; i < feature_map.size(); ++i)
	{
		float current_point = feature_map[i][1] * 255;
		if (current_line != max_x_point - 1)
		{
			if (feature_map[i][0] == -2.0f)
			{
				height_map << int(current_point) << " ";
				current_line += 1;
			}
			else
			{
				if (current_point > 255)
				{
					height_map << 255 << " ";
					current_line += 1;
				}
				else
				{
					height_map << int(current_point) << " ";
					current_line += 1;
				}
			}

		}
		else
		{
			if (feature_map[i][0] == -2.0f)
			{
				height_map << int(current_point) << std::endl;
				current_line = 0;
			}
			else
			{
				if (current_point > 255)
				{
					height_map << 255 << std::endl;
					current_line = 0;
				}
				else
				{
					height_map << int(current_point) << std::endl;
					current_line = 0;
				}
			}
		}
	}

	height_map.close();
}

void HeightGeneration::show_feature_map(std::vector<std::vector<float>> feature_map, int max_x_point)
{
	int next_line_count = 0;
	int y_value = 0;

	for (int j = 0; j < feature_map.size(); ++j)
	{
		if (next_line_count == max_x_point - 1)
		{			
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

void HeightGeneration::curve_primative(int max_x_point, int max_y_point, double seed)
{	
	std::mt19937::result_type set_seed = seed;
	std::mt19937 gen(set_seed);
	std::uniform_real_distribution<float> ridge_random_height((255.0f * ridge_height_mult), (255.0f));

	float river_max_primative_x = (river_primative_distance + 1) / float(max_x_point);
	float river_max_primative_y = (river_primative_distance + 1) / float(max_y_point);

	float river_min_primative_x = 1 / float(max_x_point);
	float river_min_primative_y = 1 / float(max_y_point);

	float river_max_distance = sqrt(pow(river_max_primative_x, 2) + pow(river_max_primative_y, 2));
	_river_min_distance = sqrt(pow(river_min_primative_x, 2) + pow(river_min_primative_y, 2));

	//---------------------RIDGE--------------------

	float ridge_max_primative_x = (ridge_primative_distance + 1) / float(max_x_point);
	float ridge_max_primative_y = (ridge_primative_distance + 1) / float(max_y_point);

	float ridge_min_primative_x = 1 / float(max_x_point);
	float ridge_min_primative_y = 1 / float(max_y_point);

	float ridge_max_distance = sqrt(pow(ridge_max_primative_x, 2) + pow(ridge_max_primative_y, 2));
	_ridge_min_distance = sqrt(pow(ridge_min_primative_x, 2) + pow(ridge_min_primative_y, 2));

	for (int i = 0; i < feature_map.size(); ++i)
	{
		if (feature_map[i][0] == -2.0f)
		{
			int x_location = i % max_x_point;
			int y_location = i / max_x_point;

			float river_height = feature_map[i][1];

			for (int y = -river_primative_distance; y <= river_primative_distance; ++y)
			{
				for (int x = -river_primative_distance; x <= river_primative_distance; ++x)
				{
					if ((x == 0 && y == 0))
					{
						continue;
					}

					int new_x = x_location + x;
					int new_y = y_location + y;

					if ((new_x > -1 && new_y > -1 && new_x < max_x_point && new_y < max_y_point))
					{
						set_curve_height(x_location, y_location, new_x, new_y, river_max_distance, max_x_point, river_height, river_angle_multiplier, 1);
					}
				}
			}
		}
	}
}

void HeightGeneration::set_curve_height(int x_location, int y_location, int new_x, int new_y, float max_distance, int max_x_point, float height, float angle_multiplier, int feature_type) // 1 == river, 2 == ridge
{
	float type = feature_map[((new_y * max_x_point) + new_x)][0];
	float old_height = feature_map[((new_y * max_x_point) + new_x)][1];
	float old_weight = feature_map[((new_y * max_x_point) + new_x)][2];

	float get_new_x = new_x / _max_x_point;
	float get_new_y = new_y / _max_y_point;

	float get_old_x = x_location / _max_x_point;
	float get_old_y = y_location / _max_y_point;

	float distance = (sqrt(pow(get_new_x - get_old_x, 2) + pow(get_new_y - get_old_y, 2)));
	float cross_section_height = tan(angle_multiplier) * distance;

	float point_elevation;

	if (feature_type == 1)
	{
		point_elevation = (height + cross_section_height);
	}
	else if (feature_type == 2)
	{
		point_elevation = (height - cross_section_height);
	}
	

	float new_weight;

	if (distance < max_distance)
	{
		new_weight = pow((1 - pow((distance / max_distance), 2)), 3);
	}
	else
	{
		new_weight = 0;
	}
	
	if (type == -1.0f && old_weight == -1.0f)
	{
		feature_map[((new_y * max_x_point) + new_x)][1] = point_elevation;
		feature_map[((new_y * max_x_point) + new_x)][2] = new_weight;
	}

	else if (feature_type == 1 && type == -1.0f && old_height > 0)
	{
		feature_map[((new_y * max_x_point) + new_x)][1] = ((old_height * old_weight) + (point_elevation * new_weight)) / (float)(old_weight + new_weight);
		feature_map[((new_y * max_x_point) + new_x)][2] = old_weight + new_weight;
	}
}

std::vector<std::vector<float>> HeightGeneration::get_feature_map()
{
	return feature_map;
}