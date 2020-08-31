#include "HeightGeneration.h"

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
		if (colours[m + 1] == 1.0f)
		{
			feature_map.push_back({ -3.0f, colours[m + 3] });
		}
		else if (colours[m + 3] != 1.0f)
		{
			feature_map.push_back({ -2.0f, colours[m + 3] });
		}
		else 
		{
			feature_map.push_back({ -1.0f, 0.0f });
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
				std::cout << "|" << std::endl;
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
				std::cout << "|" << " ";
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

		if (feature_map[i][0] == -1.0f)
		{
			continue;
		}
		else
		{
			int x_location = i % max_x_point;
			int y_location = i / max_x_point;
	
			float cross_section = feature_map[i][1];

			for (int y = 0; y < primative_distance; ++y)
			{
				for (int x = 0; x < primative_distance; ++x)
				{
					int new_x = x_location + x;
					int new_y = y_location + y;

					if (new_x < max_x_point)
					{
						if (new_y < max_y_point)
						{
							set_curve_height(x_location, y_location, new_x, new_y, max_distance, max_x_point);
						}
					}
				}
			}

			for (int y = 0; y > -primative_distance; --y)
			{
				for (int x = 0; x > -primative_distance; --x)
				{
					int new_x = x_location + x;
					int new_y = y_location + y;

					if (new_x > 0)
					{
						if (new_y > 0)
						{
							set_curve_height(x_location, y_location, new_x, new_y, max_distance, max_x_point);
						}
					}
				}
			}

			for (int y = 0; y > -primative_distance; --y)
			{
				for (int x = 0; x < primative_distance; ++x)
				{
					int new_x = x_location + x;
					int new_y = y_location + y;

					if (new_x < max_x_point)
					{
						if (new_y > 0)
						{
							set_curve_height(x_location, y_location, new_x, new_y, max_distance, max_x_point);
						}
					}
				}
			}

			for (int y = 0; y < primative_distance; ++y)
			{
				for (int x = 0; x > -primative_distance; --x)
				{
					int new_x = x_location + x;
					int new_y = y_location + y;

					if (new_x > 0)
					{
						if (new_y < max_y_point)
						{
							set_curve_height(x_location, y_location, new_x, new_y, max_distance, max_x_point);
						}
					}
				}
			}
		}
	}
}

void HeightGeneration::set_curve_height(int x_location, int y_location, int new_x, int new_y, float max_distance, int max_x_point)
{
	float distance = sqrt(pow(new_x - x_location, 2) + pow(new_y - y_location, 2));
	float normalise_distance = distance / max_distance;
	float signed_distance = 1 - normalise_distance;
	feature_map[((new_y * max_x_point) + new_x)][1] = signed_distance;

	float current_height = feature_map[((new_y * max_x_point) + new_x)][1];
	float type = feature_map[((new_y * max_x_point) + new_x)][0];

	//std::cout << type << std::endl;
	//std::cout << distance << " " << normalise_distance << std::endl;
	
	
	//if (type == -1.0f && current_height != 0)
	//{
	//	//feature_map[((new_y * max_x_point) + new_x)][1] = blend_height(max_distance, distance);
	//}
	//else
	//{
	//	feature_map[((new_y * max_x_point) + new_x)][1] = signed_distance;
	//}
}

//float HeightGeneration::blend_height(float max_distance, float distance)
//{
//	float weight = pow((1 - pow((distance / max_distance), 2)), 3);
//
//	//float elevation = 
//}

std::vector<std::vector<float>> HeightGeneration::get_feature_map()
{
	return feature_map;
}

std::vector<glm::vec2> HeightGeneration::get_location_map()
{
	return location_map;
}