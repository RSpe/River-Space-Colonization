#include "HeightGeneration.h"

const std::vector<glm::vec2> HeightGeneration::create_base_heights(int window_width, int window_height, int min_x_point, int max_x_point, int min_y_point, int max_y_point, std::vector<float> tree_colour, std::vector<float> ridge_colour)
{
	std::vector<glm::vec2> height_map;

	glReadBuffer(GL_FRONT);

	//GLfloat pixels[50][50][3];

	int read_point_x = (window_width / 2) - (max_x_point / 2);
	int read_point_y = (window_height / 2) - (max_y_point / 2);

	int pixel_count = 3 * max_x_point * max_y_point;

	//glReadPixels(read_point_x, read_point_y, max_x_point, max_y_point, GL_RGB, GL_FLOAT, &pixels);
	std::vector<GLfloat> pixels(pixel_count);

	glReadPixels(read_point_x, read_point_y, max_x_point, max_y_point, GL_RGB, GL_FLOAT, pixels.data());

	//std::cout << sizeof(pixels) << std::endl;
	int next_line_count = 0;
	//std::reverse(pixels.begin(), pixels.end());

	for (int n = 0; n != max_y_point / 2; ++n) 
	{
		std::swap_ranges(pixels.begin() + 3 * max_x_point * n, pixels.begin() + 3 * max_x_point * (n + 1), pixels.begin() + 3 * max_x_point * (max_y_point - n - 1));
	}

	for (int i = 0; i < pixel_count; i += 3)
	{
		next_line_count += 1;
		if (next_line_count == max_y_point)
		{
			if (pixels[i] == tree_colour[0] && pixels[i + 1] == tree_colour[1] && pixels[i + 2] == tree_colour[2])
			{
				std::cout << 0 << std::endl;
			}
			else
			{
				std::cout << 1 << std::endl;
				next_line_count = 0;
			}
		}
		else
		{
			if (pixels[i] == ridge_colour[0] && pixels[i + 1] == ridge_colour[1] && pixels[i + 2] == ridge_colour[2])
			{
				std::cout << 0 << " ";
			}
			else
			{
				std::cout << 1 << " ";
			}
		}

	}

	return height_map;
}