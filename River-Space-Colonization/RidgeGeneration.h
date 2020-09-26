#pragma once

#include "Include.h"

class RidgeGeneration
{
public:
	static const std::vector<std::vector<glm::vec2>> generate_ridges(int num_ridges, double seed, int point_resolution, std::vector<glm::vec2> random_roots);

private:
	static double distance(glm::vec2 point1, glm::vec2 point2);
};

