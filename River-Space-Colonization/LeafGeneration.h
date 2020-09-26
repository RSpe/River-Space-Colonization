#pragma once

#include "Include.h"

class LeafGeneration
{
public:
	static const std::vector<glm::vec2> generate_leaves(int num_leaves, double seed, int tree_num, int max_x_point, int min_x_point, int max_y_point, int min_y_point);
};

