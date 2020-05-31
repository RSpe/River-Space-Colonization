#include "RidgeGeneration.h"

/* Not random for now! */
const std::vector<glm::vec2> RidgeGeneration::generate_ridges(int num_ridges, int seed)
{
	std::vector<glm::vec2> random_ridges;

	srand(seed);

	random_ridges.push_back(glm::vec2(-300.0f, 0.0f));
	random_ridges.push_back(glm::vec2(300.0f, 400.0f));
	random_ridges.push_back(glm::vec2(450.0f, -450.0f));
	random_ridges.push_back(glm::vec2(450.0f, 450.0f));
	random_ridges.push_back(glm::vec2(-400.0f, -100.0f));
	random_ridges.push_back(glm::vec2(-100.0f, -400.0f));

	return random_ridges;
}