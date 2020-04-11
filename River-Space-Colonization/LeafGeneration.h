#pragma once

#include "TestTreeSpaceColonisation.h"

class LeafGeneration
{
public:
	static const std::vector<glm::vec2> generate_leaves(int num_leaves, int seed);
};
