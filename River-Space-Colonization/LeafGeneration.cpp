#include "LeafGeneration.h"

const std::vector<glm::vec2> LeafGeneration::generate_leaves(int num_leaves, int seed)
{
	std::vector<glm::vec2> random_leaves;

	srand(seed);

	//int x_low = -600 + 100;
	//int x_high = 600 + 100;
	//int y_low = -600 + 100;
	//int y_high = 600 + 100;

	int x_low = -500;
	int x_high = 500;
	int y_low = -500;
	int y_high = 500;

	for (int i = 0; i < num_leaves; i++) 
	{
		//glm::vec2 xy_position = glm::vec2((x_low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (x_high - x_low)))), (y_low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (y_high - y_low)))));
		glm::vec2 xy_position = glm::vec2((x_low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (x_high - x_low)))), (y_low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (y_high - y_low)))));
		random_leaves.push_back(xy_position); 
	}
	return random_leaves;
}