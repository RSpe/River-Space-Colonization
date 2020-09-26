#include "LeafGeneration.h"

#include <functional>

const std::vector<glm::vec2> LeafGeneration::generate_leaves(int num_leaves, double seed, int tree_num, int max_x_point, int min_x_point, int max_y_point, int min_y_point)
{
	float min_x = min_x_point;
	float min_y = min_y_point;
	float max_x = max_x_point;
	float max_y = max_y_point;

	std::vector<glm::vec2> random_leaves;
	std::vector<glm::vec2> random_roots;

	float max_float = std::max(abs(max_x_point + 1), abs(max_y_point + 1));
	int min_index = -1;

	std::mt19937::result_type set_seed = seed;
	std::mt19937 gen(set_seed);
	std::uniform_real_distribution<float> x_pos(min_x_point, max_x_point);
	std::uniform_real_distribution<float> y_pos(min_y_point, max_y_point);

	int current_size = 0;

	for (int i = 0; i < num_leaves + tree_num + 1; i++)
	{
		glm::vec2 xy_position = glm::vec2(x_pos(gen), y_pos(gen));

		float find_max_float = std::max(abs(xy_position[0]), abs(xy_position[1]));

		if (current_size < tree_num)
		{
			random_roots.push_back(xy_position);
			current_size += 1;
		}

		else if (current_size == tree_num)
		{
			if (i == current_size + 1)
			{
				for (int j = 0; j < tree_num; ++j)
				{
					float find_max_min = std::max(abs(random_roots[j][0]), abs(random_roots[j][1]));

					if (find_max_min < max_float)
					{
						max_float = find_max_min;
						min_index = j;
					}									
				}
			}

			else if (find_max_float > max_float)
			{
				random_leaves.push_back(random_roots[min_index]);
				random_roots[min_index] = xy_position;
				max_float = find_max_float;

				for (int j = 0; j < tree_num; ++j)
				{
					float find_max_min = std::max(abs(random_roots[j][0]), abs(random_roots[j][1]));

					if (find_max_min < max_float)
					{
						max_float = find_max_min;
						min_index = j;
					}
				}
			}
			else
			{
				random_leaves.push_back(xy_position);
			}
		}
	}

	random_leaves.insert(random_leaves.end(), random_roots.begin(), random_roots.end());
	
	return random_leaves;
}