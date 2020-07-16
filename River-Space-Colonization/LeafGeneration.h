#pragma once

#include "Include.h"

class LeafGeneration
{
public:
	static const std::vector<glm::vec2> generate_leaves(int num_leaves, double seed, int tree_num, float min_x, float max_x, float min_y, float max_y);
};

