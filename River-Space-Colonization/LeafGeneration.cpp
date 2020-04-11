#include "LeafGeneration.h"

const std::vector<glm::vec2> LeafGeneration::generate_leaves(int num_leaves, int seed)
{
	std::vector<glm::vec2> random_leaves;

	srand(seed);

	int low = -1;
	int high = 1;

	for (int i = 0; i < num_leaves; i++) 
	{
		glm::vec2 xy_position = glm::vec2((low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low))), low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)))));
		random_leaves.push_back(xy_position);
	}
	return random_leaves;
}