#include "HeightGeneration.h"

void HeightGeneration::generate_maps(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour, std::vector<std::shared_ptr<Branch>> branches)
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

	int rgb_count = 3 * max_x_point * max_y_point;

	std::vector<GLfloat> colours(rgb_count);

	glReadPixels(read_point_x, read_point_y, max_x_point, max_y_point, GL_RGB, GL_FLOAT, colours.data());

	for (int n = 0; n != max_y_point / 2; ++n) 
	{
		std::swap_ranges(colours.begin() + 3 * max_x_point * n, colours.begin() + 3 * max_x_point * (n + 1), colours.begin() + 3 * max_x_point * (max_y_point - n - 1));
	}

	std::cout << glm::to_string(branches[0]->get_parent()) << " " << glm::to_string(branches[0]->get_position()) << " " << glm::to_string(branches[0]->get_direction()) << std::endl;

	int next_line_count = 0;

	for (int m = 0; m < colours.size(); m += 3)
	{
		if (next_line_count == max_x_point - 1)
		{
			if (colours[m] == tree_colour[0] && colours[m + 1] == tree_colour[1] && colours[m + 2] == tree_colour[2])
			{
				//height_map.push_back(255.0f);
				std::cout << 1 << std::endl;
			}
			else if (colours[m] == ridge_colour[0] && colours[m + 1] == ridge_colour[1] && colours[m + 2] == ridge_colour[2])
			{
				//height_map.push_back(-1.0f);
				std::cout << 2 << std::endl;
			}
			else
			{
				//height_map.push_back(0.0f);
				std::cout << 0 << std::endl;
			}
			next_line_count = 0;
		}
		else
		{
			if (colours[m] == tree_colour[0] && colours[m + 1] == tree_colour[1] && colours[m + 2] == tree_colour[2])
			{
				std::cout << 5 << " ";
			}
			else if (colours[m] == ridge_colour[0] && colours[m + 1] == ridge_colour[1] && colours[m + 2] == ridge_colour[2])
			{
				std::cout << 255 << " ";
			}
			else
			{
				std::cout << 0 << " ";
			}
			next_line_count += 1;
		}
	}
	terrian_interpolation();
}

void HeightGeneration::terrian_interpolation()
{

}

std::vector<float> HeightGeneration::get_height_map()
{
	return height_map;
}

std::vector<glm::vec2> HeightGeneration::get_location_map()
{
	return location_map;
}