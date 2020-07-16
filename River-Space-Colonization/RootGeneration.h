#pragma once

#include "Include.h"

class RootGeneration
{
public:
	static const std::vector<glm::vec2> generate_roots(int num_roots, double seed, int window_width, int window_height);
};

