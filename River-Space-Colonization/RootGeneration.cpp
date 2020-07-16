#include "RootGeneration.h"

// TODO: Assumes square window size
const std::vector<glm::vec2> RootGeneration::generate_roots(int num_roots, double seed, int window_width, int window_height)
{
	srand(seed);

	int min_width = (window_width * -1);
	int max_width = window_width;
	int min_height = (window_height * -1);
	int max_height = window_height;

	std::vector<glm::vec2> random_roots;

	for (int i = 0; i < num_roots; i++)
	{
		int random_edge = rand() % 2; // Get a random start on x or y axis.

		if (random_edge == 0.0f) // x axis
		{
			int random_side = rand() % 2; // Get a random start on left of the right side.
			if (random_side == 0.0f)
			{
				glm::vec2 root_position = glm::vec2((min_width + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_width - min_width)))), max_width);
				random_roots.push_back(root_position);
			}
			else 
			{
				glm::vec2 root_position = glm::vec2((min_width + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_width - min_width)))), min_width);
				random_roots.push_back(root_position);
			}
		}
		else // y axis
		{
			int random_side = rand() % 2;
			if (random_side == 0.0f)
			{
				glm::vec2 root_position = glm::vec2(max_height, (min_height + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_height - min_height)))));
				random_roots.push_back(root_position);
			}
			else
			{
				glm::vec2 root_position = glm::vec2(min_height, (min_height + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_height - min_height)))));
				random_roots.push_back(root_position);
			}
		}
	}

	return random_roots;
}
