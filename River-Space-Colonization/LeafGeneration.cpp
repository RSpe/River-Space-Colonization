#include "LeafGeneration.h"

const std::vector<glm::vec2> LeafGeneration::generate_leaves(int num_leaves, double seed, int tree_num, float min_x, float max_x, float min_y, float max_y)
{
	srand(seed);

	std::vector<glm::vec2> random_leaves;
	std::vector<glm::vec2> random_roots;

	glm::vec3 current_min = glm::vec3(max_x, max_y, -1.0f);


	for (int i = 0; i < num_leaves + tree_num; i++)
	{
		glm::vec2 xy_position = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));

		float current_absolute = std::max(abs(xy_position[0]), abs(xy_position[1]));

		float min = std::max(abs(current_min[0]), abs(current_min[1]));

		if (random_roots.size() < tree_num)
		{
			if (current_min[2] == -1.0f)
			{
				current_min = glm::vec3(xy_position[0], xy_position[1], random_roots.size());
				random_roots.push_back(xy_position);
				continue;
			}
			else if (current_absolute > min)
			{
				random_roots.push_back(xy_position);
				continue;
			}
		}

		else if (current_absolute > min)
		{
			random_roots[current_min[2]] = glm::vec2(xy_position[0], xy_position[1]);
			random_leaves.push_back(glm::vec2(current_min[0], current_min[1]));

			float find_new_min = 3.0f; // Larger than the total window size

			for (int k = 0; k < tree_num; ++k)
			{
				float check_root = std::max(abs(random_roots[k][0]), abs(random_roots[k][1]));

				if (check_root < find_new_min)
				{
					current_min = glm::vec3(random_roots[k][0], random_roots[k][1], k);
					find_new_min = check_root;
				}
			}
			continue;
		}
		random_leaves.push_back(xy_position);
	}

	random_leaves.insert(random_leaves.end(), random_roots.begin(), random_roots.end());

	return random_leaves;
}